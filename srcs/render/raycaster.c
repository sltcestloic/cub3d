/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:19:24 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/03 14:56:44 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->camx = 0;
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->dirx = 0;
	ray->diry = 0;
	ray->drawend = 0;
	ray->drawstart = 0;
	ray->hit = 0;
	ray->lineheight = 0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->perpwalldist = 0;
	ray->side = 0;
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->stepx = 0;
	ray->stepy = 0;
}

void	do_dda(t_view *view, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (view->map->content[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

void 	calculate_side_dist(t_view *view, t_ray *ray)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (view->player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - view->player->posx) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (view->player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - view->player->posy) * ray->deltadisty;
	}
}

void	draw(t_view *view, t_ray *ray, int x)
{
	int	line_height;
	int	view_height;
	int color = rgbint(0, 255, 0);
	
	view_height = view->settings->height;
	line_height = view_height / ray->perpwalldist;
	ray->drawstart = -line_height / 2 + view_height / 2;
	ray->drawstart += view->horizon;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = line_height / 2 + view_height / 2;
	ray->drawend += view->horizon;
	if (view->keyboard->ctrl_pressed)
	{
		ray->drawstart -= 50;
		ray->drawend -= 50;
	}
	if (ray->drawend > view->settings->height)
		ray->drawend = view->settings->height;
	if (ray->side == 0)
		color /= 2;
	for (int y = 0; y < ray->drawstart; y++)
		put_pixel(view->image, x, y, view->settings->sky_color);
	for (int y = ray->drawstart; y < ray->drawend; y++)
		put_pixel(view->image, x, y, color);
	for (int y = ray->drawend; y < view->settings->height; y++)
		put_pixel(view->image, x, y, view->settings->ground_color);
}

void	do_raycast(t_view *view)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < view->settings->width)
	{
		init_ray(&ray);
		ray.camx = ((2 * x) / (double)view->settings->width) - 1;
		//printf("x = %d cam x = %f width = %d\n", x, ray.camx, view->settings->width);
		ray.dirx = view->player->dirx + view->player->planex * ray.camx;
	//	printf("dir x %f\n", ray.dirx);
		ray.diry = view->player->diry + view->player->planey * ray.camx;
	//	printf("dir y %f\n", ray.diry);
		ray.mapx = (int)view->player->posx;
		ray.mapy = (int)view->player->posy;
		ray.deltadistx = fabs(1 / ray.dirx);
		//printf("fabs(1 / %f) = %f\n", ray.dirx, ray.deltadistx);
		ray.deltadisty = fabs(1 / ray.diry);
		//printf("fabs(1 / %f) = %f\n", ray.diry, ray.deltadisty);
		calculate_side_dist(view, &ray);
		do_dda(view, &ray);
		if (ray.side == 0)
			ray.perpwalldist = (ray.mapx - view->player->posx + (1 - ray.stepx) / 2) / ray.dirx;
		else
			ray.perpwalldist = (ray.mapy - view->player->posy + (1 - ray.stepy) / 2) / ray.diry;
		//printf("dist = %f\n", ray.perpwalldist);
		draw(view, &ray, x);
		x++;
	}
}
