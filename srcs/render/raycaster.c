/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:19:24 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/08 16:52:22 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_ray *ray, int x, double width)
{
	ray->cam_x = ((2 * x) / width) - 1;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->draw_end = 0;
	ray->draw_start = 0;
	ray->hit = 0;
	ray->line_height = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->wall_dist = 0;
	ray->side = 0;
	ray->side_x = 0;
	ray->side_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
}

void	do_dda(t_view *view, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = ray->step_x == 1 ? EAST : WEST;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = ray->step_y == 1 ? SOUTH : NORTH;
		}
		if (view->map->content[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_side_dist(t_view *view, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (view->player->posx - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1 - view->player->posx) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (view->player->posy - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1 - view->player->posy) * ray->delta_y;
	}
}

void	set_ray_height(t_view *view, t_ray *ray)
{
	int	line_height;
	int	view_height;

	view_height = view->settings->height;
	line_height = view_height / ray->wall_dist;
	ray->draw_start = -line_height / 2 + view_height / 2;
	ray->draw_start += view->horizon;
	ray->draw_end = line_height / 2 + view_height / 2;
	ray->draw_end += view->horizon;
	if (view->keyboard->ctrl_pressed)
	{
		ray->draw_start -= 50;
		ray->draw_end -= 50;
	}
}

void	do_raycast(t_view *view)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < view->settings->width)
	{
		init_ray(&ray, x, (double)view->settings->width);
		ray.dir_x = view->player->dirx + view->player->planex * ray.cam_x;
		ray.dir_y = view->player->diry + view->player->planey * ray.cam_x;
		ray.map_x = (int)view->player->posx;
		ray.map_y = (int)view->player->posy;
		ray.delta_x = fabs(1 / ray.dir_x);
		ray.delta_y = fabs(1 / ray.dir_y);
		calculate_side_dist(view, &ray);
		do_dda(view, &ray);
		if (ray.side == EAST || ray.side == WEST)
			ray.wall_dist = (ray.map_x - view->player->posx +
				(1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.wall_dist = (ray.map_y - view->player->posy +
				(1 - ray.step_y) / 2) / ray.dir_y;
		view->z_buffer[x] = ray.wall_dist;
		set_ray_height(view, &ray);
		draw_ray(view, &ray, x);
		x++;
	}
}
