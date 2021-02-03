/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:57:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/03 14:52:53 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	init_window(t_settings settings, t_view view)
{
	t_mouse		mouse;
	t_keyboard	keyboard;

	view.window = mlx_new_window(view.mlx, settings.width, settings.height,
			"Cub3D");
	mouse.x = -1;
	mouse.y = -1;
	mouse.pressed = FALSE;
	keyboard.w_pressed = FALSE;
	keyboard.a_pressed = FALSE;
	keyboard.s_pressed = FALSE;
	keyboard.d_pressed = FALSE;
	keyboard.la_pressed = FALSE;
	keyboard.ra_pressed = FALSE;
	keyboard.ua_pressed = FALSE;
	keyboard.da_pressed = FALSE;
	keyboard.shift_pressed = FALSE;
	keyboard.ctrl_pressed = FALSE;
	view.mouse = &mouse;
	view.keyboard = &keyboard;
	mlx_mouse_hide();
	init_hooks(view);
}
