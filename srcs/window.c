/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:57:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/26 15:21:46 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_window(t_view *view, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < view->settings->width)
	{
		while (y < view->settings->height)
		{
			mlx_pixel_put(view->mlx, view->window, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

void	init_hooks(t_view view)
{
	mlx_hook(view.window, 4, 1L << 2, handle_click, &view);
	mlx_hook(view.window, 5, 1L << 3, handle_click_release, &view);
	mlx_hook(view.window, 2, 1L << 0, handle_key_press, &view);
	mlx_hook(view.window, 3, 1L << 1, handle_key_release, &view);
	mlx_hook(view.window, 17, 1L << 17, handle_close_button, 0);
	mlx_hook(view.window, 6, 1L << 6, handle_mouse_motion, &view);
	mlx_loop_hook(view.mlx, render_frame, &view);
	mlx_loop(view.mlx);
}

void	init_keyboard(t_keyboard *keyboard)
{
	keyboard->w_pressed = FALSE;
	keyboard->a_pressed = FALSE;
	keyboard->s_pressed = FALSE;
	keyboard->d_pressed = FALSE;
	keyboard->la_pressed = FALSE;
	keyboard->ra_pressed = FALSE;
	keyboard->ua_pressed = FALSE;
	keyboard->da_pressed = FALSE;
	keyboard->shift_pressed = FALSE;
	keyboard->ctrl_pressed = FALSE;
}

void	init_window(t_settings settings, t_view view)
{
	t_mouse		mouse;
	t_image		img;
	t_keyboard	keyboard;

	view.window = mlx_new_window(view.mlx, settings.width, settings.height,
			"Cub3D");
	mouse.x = -1;
	mouse.y = -1;
	mouse.pressed = FALSE;
	init_keyboard(&keyboard);
	view.keyboard = &keyboard;
	view.mouse = &mouse;
	view.image = &img;
	view.image->img = mlx_new_image(view.mlx, view.settings->width,
		view.settings->height);
	view.image->addr = mlx_get_data_addr(view.image->img,
		&view.image->bits_per_pixel,
		&view.image->line_len, &view.image->endian);
	hide_mouse(&view);
	init_hooks(view);
}
