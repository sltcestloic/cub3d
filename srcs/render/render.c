/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:27:54 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/14 13:49:09 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_win_screen(t_view *view, int minutes, int seconds)
{
	int			x;
	int			y;
	t_texture	texture;
	char		*time;

	texture = view->settings->win_screen;
	x = (view->settings->width - texture.width) / 2;
	y = (view->settings->height - texture.height) / 2;
	fill_window(view, 0);
	mlx_put_image_to_window(view->mlx, view->window,
			texture.img, x,
			y);
	x = view->settings->width / 2 - 130;
	y = view->settings->height / 2 + 100;
	time = ft_strdup("Tu as mis ");
	time = ft_strjoin(time, ft_itoa(minutes));
	time = ft_strjoin(time, " minutes et ");
	time = ft_strjoin(time, ft_itoa(seconds));
	time = ft_strjoin(time, " secondes");
	mlx_string_put(view->mlx, view->window, x, y, 0x0FFFFFF, time);
	free(time);
}

int		render_frame(t_view *view)
{
	t_image	img;

	if (view->finished)
		return (0);
	view->frame_timestamp = current_millis();
	if (++view->animation > 15)
		view->animation = 0;
	img.img = mlx_new_image(view->mlx, view->settings->width,
		view->settings->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_len, &img.endian);
	view->image = &img;
	do_raycast(view);
	do_spritecast(view);
	mlx_put_image_to_window(view->mlx, view->window, img.img, 0, 0);
	draw_hud(view);
	draw_health(view);
	decrease_effects(view);
	draw_fps(view);
	if (view->save)
		create_bitmap(view);
	handle_keyboard(view);
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
		put_pixel(view, x, y++, get_sky_color(view));
	if (ray->side == EAST || ray->side == WEST)
		wx = view->player->pos_y + ray->wall_dist * ray->dir_y;
	else
		wx = view->player->pos_x + ray->wall_dist * ray->dir_x;
	wx -= floor(wx);
	while (y < ray->draw_end)
	{
		ty = (y - ray->draw_start) * texture.height / (ray->draw_end
			- ray->draw_start);
		tx = (wx - (int)wx) * texture.width;
		put_pixel(view, x, y++, get_texture_color(view, texture, tx, ty));
	}
	while (y < view->settings->height)
		put_pixel(view, x, y++, get_ground_color(view));
}

void	draw_sprite_stripe(t_view *view, t_sprite *sprite, int x, int tx)
{
	int			y;
	int			ty;
	t_texture	texture;

	if (sprite->type < SPRITE_CUP)
		texture = view->settings->sprite_texture[sprite->type];
	else
		texture = view->settings->cup_texture[(int)view->animation / 5];
	y = sprite->draw_start_y;
	while (y < sprite->draw_end_y)
	{
		ty = (y - sprite->draw_start_y) * texture.height /
			(sprite->draw_end_y - sprite->draw_start_y);
		put_pixel(view, x, y++, get_sprite_color(view, sprite, tx, ty));
	}
}

void	draw_sprite(t_view *view, t_sprite *sprite)
{
	int			x;
	int			y;
	int			tx;
	t_texture	texture;

	if (!sprite->visible)
		return ;
	x = sprite->draw_start_x;
	y = sprite->draw_start_y;
	if (sprite->type < SPRITE_CUP)
		texture = view->settings->sprite_texture[sprite->type];
	else
		texture = view->settings->cup_texture[(int)view->animation / 5];
	if (abs(sprite->draw_end_x - sprite->draw_start_x) > 2000)
		return ;
	while (x < sprite->draw_end_x)
	{
		tx = (x - sprite->draw_start_x) * texture.width /
			(sprite->draw_end_x - sprite->draw_start_x);
		if (sprite->tr_y > 0 && x > 0 && x < view->settings->width &&
			sprite->tr_y < view->z_buffer[x])
			draw_sprite_stripe(view, sprite, view->settings->width - x, tx);
		x++;
	}
}
