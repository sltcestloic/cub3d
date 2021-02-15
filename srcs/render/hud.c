/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:45:34 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/15 16:19:07 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_fps(t_view *view)
{
	int		fps;
	char	*fps_str;

	fps = (int)(1.0 / ((current_millis() - view->frame_timestamp) / 1000.0));
	fps_str = ft_itoa(fps);
	mlx_string_put(view->mlx, view->window, view->settings->width / 2.7 + 23,
		view->settings->height - 25, 0x0FFFFFF, fps_str);
	free(fps_str);
}

int		draw_heart(t_view *view, t_texture texture, int x)
{
	mlx_put_image_to_window(view->mlx, view->window, texture.img, x,
				view->settings->height - 15 - texture.height);
	x += texture.width;
	return (x);
}

void	draw_health(t_view *view)
{
	t_texture	health_texture;
	t_texture	empty_texture;
	int			health;
	int			x;
	int			i;

	x = view->settings->width / 2.7 + 90;
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
	mlx_put_image_to_window(view->mlx, view->window,
		view->settings->hud_texture.img,
		view->settings->width / 2.7, view->settings->height - 70);
}
