/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:57:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 13:38:06 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_window(t_settings settings)
{
	t_view		view;
	t_mouse		mouse;
	t_keyboard	keyboard;
	t_circle	circle;

	view.mlx = mlx_init();
	view.window = mlx_new_window(view.mlx, settings.width, settings.height, "Cub3D");
	mouse.x = -1;
	mouse.y = -1;
	mouse.pressed = 0;
	keyboard.w_pressed = 0;
	keyboard.a_pressed = 0;
	keyboard.s_pressed = 0;
	keyboard.d_pressed = 0;
	circle.x = settings.width / 2;
	circle.y = settings.height / 2;
	view.settings = &settings;
	view.mouse = &mouse;
	view.keyboard = &keyboard;
	view.circle = &circle;
	mlx_hook(view.window, 4, 1L<<2, handle_click, &view);
	mlx_hook(view.window, 5, 1L<<3, handle_click_release, &view);
	mlx_hook(view.window, 2, 1L<<0, handle_key_press, &view);
	mlx_hook(view.window, 3, 1L<<1, handle_key_release, &view);
	mlx_hook(view.window, 17, 1L<<17, handle_close_button, 0);
	mlx_loop_hook(view.mlx, render_frame, &view);
	mlx_loop(view.mlx);
}
