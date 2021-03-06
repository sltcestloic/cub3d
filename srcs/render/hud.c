/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:45:34 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/06 13:31:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_fps(t_view *view)
{
	int		fps;
	char	*fps_str;

	if (view->settings->width < 500 || view->settings->height < 300)
		return ;
	fps = (int)(1.0 / ((current_millis() - view->frame_timestamp) / 1000.0));
	if (fps < 0)
		fps = 0;
	if (view->animation == 0)
		view->fps = fps;
	fps_str = ft_itoa(view->fps);
	mlx_string_put(view->mlx, view->window, view->settings->width / 2.56,
		view->settings->height * 0.97, 0x0FFFFFF, fps_str);
	free(fps_str);
}

int		draw_heart(t_view *view, t_texture texture, int x)
{
	double		ratio_x;
	double		ratio_y;
	int			y;
	int			old_x;

	old_x = x;
	y = view->settings->height * 0.93;
	ratio_y = 700.0 / view->settings->height;
	ratio_x = 1000.0 / view->settings->width;
	while (y - (view->settings->height * 0.93) < texture.height / ratio_y)
	{
		x = old_x;
		while (x - old_x < texture.width / ratio_x)
		{
			put_pixel_ignore_black(view, x, y, texture.addr[(int)((y -
				(view->settings->height * 0.93)) * ratio_y) * texture.width +
				(int)((x - old_x) * ratio_x)]);
			x++;
		}
		y++;
	}
	return (x + 1);
}

void	draw_health(t_view *view)
{
	t_texture	health_texture;
	t_texture	empty_texture;
	int			health;
	int			x;
	int			i;

	if (view->settings->height < 20 || view->settings->width < 20)
		return ;
	x = view->settings->width / 2.155;
	health = view->player->health - 1;
	health_texture = view->settings->sprite_texture[SPRITE_HEALTH];
	empty_texture = view->settings->heart_empty_texture;
	i = 0;
	while (i < MAX_HEALTH)
	{
		if (health >= i)
			x = draw_heart(view, health_texture, x);
		else
			x = draw_heart(view, empty_texture, x);
		i++;
	}
}

void	draw_hud(t_view *view)
{
	double		ratio_x;
	double		ratio_y;
	t_texture	texture;
	int			x;
	int			y;

	texture = view->settings->hud_texture;
	x = view->settings->width / 2.7;
	y = view->settings->height * 0.9;
	ratio_x = (double)texture.width / (int)((int)(view->settings->width
		/ 1.507) - x);
	ratio_y = (double)texture.height / (view->settings->height - y);
	while (x < (int)(view->settings->width / 1.507))
	{
		y = view->settings->height * 0.9;
		while (y < view->settings->height)
		{
			put_pixel(view, x, y, texture.addr[(int)((y -
				(view->settings->height * 0.9)) * ratio_y) * texture.width
				+ (int)((x - (view->settings->width / 2.7)) * ratio_x)]);
			y++;
		}
		x++;
	}
}
