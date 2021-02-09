/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:27:54 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/09 15:15:20 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		render_frame(t_view *view)
{
	t_image	img;

	img.img = mlx_new_image(view->mlx, view->settings->width,
		view->settings->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_len, &img.endian);
	view->image = &img;
	handle_keyboard(view);
	do_raycast(view);
	do_spritecast(view);
	mlx_put_image_to_window(view->mlx, view->window, img.img, 0, 0);
	return (0);
}

void	draw_ray(t_view *view, t_ray *ray, int x)
{
	int			y;
	double		wx;
	int			tx;
	int			ty;
	t_texture	texture;

	y = 0;
	texture = get_texture(ray->side, view);
	while (y < ray->draw_start)
		put_pixel(view, x, y++, view->settings->sky_color);
	if (ray->side == EAST || ray->side == WEST)
		wx = view->player->posy + ray->wall_dist * ray->dir_y;
	else
		wx = view->player->posx + ray->wall_dist * ray->dir_x;
	wx -= floor(wx);
	while (y < ray->draw_end)
	{
		ty = (y - ray->draw_start) * texture.height / (ray->draw_end
			- ray->draw_start);
		tx = (wx - (int)wx) * texture.width;
		put_pixel(view, x, y++, texture.addr[(ty * texture.width) + tx]);
	}
	while (y < view->settings->height)
		put_pixel(view, x, y++, view->settings->ground_color);
}

void	draw_sprite_stripe(t_view *view, t_sprite *sprite, int x, int tx)
{
	int			y;
	int			ty;
	t_texture	texture;

	texture = view->settings->sprite_texture;
	y = sprite->draw_start_y;
	while (y < sprite->draw_end_y)
	{
		ty = (y - sprite->draw_start_y) * texture.height /
			(sprite->draw_end_y - sprite->draw_start_y);
		put_pixel(view, x, y++, view->settings->
			sprite_texture.addr[(texture.width * ty) + tx]);
	}
}

void	draw_sprite(t_view *view, t_sprite *sprite)
{
	int			x;
	int			y;
	int			tx;
	t_texture	texture;

	x = sprite->draw_start_x;
	y = sprite->draw_start_y;
	texture = view->settings->sprite_texture;
	while (x < sprite->draw_end_x)
	{
		tx = (x - sprite->draw_start_x) * texture.width /
			(sprite->draw_end_x - sprite->draw_start_x);
		if (sprite->tr_y > 0 && x > 0 && x < view->settings->width &&
			sprite->tr_y < view->z_buffer[x])
		{
			draw_sprite_stripe(view, sprite, x, tx);
		}
		x++;
	}
}
