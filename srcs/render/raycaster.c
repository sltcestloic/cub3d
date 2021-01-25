/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:19:24 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/25 10:37:45 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->drawstart = 0;
	ray->drawend = 0;
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
	ray->camx = 0;
}

void	update_sidedist(t_player *player, t_ray *ray)
{
	if (player->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - player->posx) * ray->deltadistx;
	}
	if (player->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - player->posy) * ray->deltadisty;
	}
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
			ray->perpwalldist = (ray->mapx - view->player->posx + (1 - ray->stepx) / 2) / ray->dirx;
			//printf("(%d - %f + (1 - %d) / 2) / %f = %d\n", ray->mapx, view->player->posx, ray->stepx, ray->dirx, ray->perpwalldist);
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
			ray->perpwalldist = (ray->mapy - view->player->posy + (1 - ray->stepy) / 2) / ray->diry;
			//printf("(%d - %f + (1 - %d) / 2) / %f = %d\n", ray->mapy, view->player->posy, ray->stepy, ray->diry, ray->perpwalldist);

		}
		//printf("y %d x %d dist %d\n", ray->mapy, ray->mapx, ray->perpwalldist);
		if (view->map->content[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
		//printf("hit=%d\n", ray->hit);
	}
}

void	draw_ray(t_view *view, t_ray *ray, t_image *img, int x)
{
	int		height;

	height = view->settings->height;

	ray->lineheight = (int)(height / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + height / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + height / 2;
	if (ray->drawend >= height)
		ray->drawend = height - 1;
	int color = rgbint(0, 255, 0);
	if (ray->side == 1)
		color = rgbint(0, 180, 0);
	for (int y = ray->drawstart; y < ray->drawend; y++)
		put_pixel_to_img(img, x, y, color);
}

void	do_raycast(t_view *view)
{
	int		x;
	t_ray	ray;
	t_image	img;

	x = 0;
	img.img = mlx_new_image(view->mlx, view->settings->width, view->settings->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	while (x < view->settings->width)
	{
		init_ray(&ray);
		ray.mapx = view->player->posx;
		ray.mapy = view->player->posy;
		ray.camx = 2 * x / view->settings->width - 1;
		ray.dirx = view->player->dirx + view->player->planex * ray.camx;
		ray.diry = view->player->diry + view->player->planey * ray.camx;
		ray.deltadistx = fabs(1 / ray.dirx);
		ray.deltadisty = fabs(1 / ray.diry);
		update_sidedist(view->player, &ray);
		do_dda(view, &ray);
		draw_ray(view, &ray, &img, x);
		x++;
	}
	mlx_put_image_to_window(view->mlx, view->window, img.img, 0, 0);
}
