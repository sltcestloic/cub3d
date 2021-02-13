/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:45:34 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/13 13:53:54 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_fps(t_view *view)
{
	int		fps;

	fps = (int)(1.0 / ((current_millis() - view->frame_timestamp) / 1000.0));
	mlx_string_put(view->mlx, view->window, 0, 20, 0x0FFFFFF, "FPS: ");
	mlx_string_put(view->mlx, view->window, 30, 20, 0x0FFFFFF, ft_itoa(fps));
}

void	draw_health(t_view *view)
{
	t_texture	health_texture;
	int			health;
	int			x;

	x = view->settings->width / 2 - 80;
	health = view->player->health;
	health_texture = view->settings->sprite_texture[SPRITE_HEALTH];
	while (health)
	{
		mlx_put_image_to_window(view->mlx, view->window, health_texture.img, x,
			view->settings->height - 7 - health_texture.height);
		x += health_texture.width;
		health--;
	}
}

void	draw_hud(t_view *view)
{
	int			x;
	int			y;

	x = view->settings->width / 2 - 80;
	y = view->settings->height - 50;
	while (y < view->settings->height)
	{
		while (x < view->settings->width / 2 + 80)
		{
			put_pixel(view, x, y, rgbint(51, 129, 255));
			x++;
		}
		x = view->settings->width / 2 - 80;
		y++;
	}
}
