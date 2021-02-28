/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:39:20 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/28 11:49:28 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_scaled_win_screen(t_view *view)
{
	double		ratio_x;
	double		ratio_y;
	t_texture	texture;
	int			x;
	int			y;

	texture = view->settings->win_screen;
	ratio_x = (double)texture.width / view->settings->width;
	ratio_y = (double)texture.height / view->settings->height;
	x = 0;
	y = 0;
	while (y < view->settings->height)
	{
		x = 0;
		while (x < view->settings->width)
		{
			mlx_pixel_put(view->mlx, view->window, x, y, texture.addr[(int)
				((int)(y * ratio_y) * texture.width + (int)(x * ratio_x))]);
			x++;
		}
		y++;
	}
}
