/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:57:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 09:30:41 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		handle_click(int button, int x, int y, t_view *view)
{
	printf("press %d %d %d\n", button, x, y);
	if (button == 1)
		view->mouse->pressed = 1;
	return (0);
}

int		handle_click_release(int button, int x, int y, t_view *view)
{
	printf("release %d %d %d\n", button, x, y);
	if (button == 1)
		view->mouse->pressed = 0;
	return (0);
}

int		handle_keypress(int keycode, t_view *view)
{
	if (keycode == 53)
	{
   		mlx_destroy_window(view->mlx, view->window);
		exit(0);
	}
	return (0);
}

int		handle_close_button()
{
	exit(0);
	return (0);
}

void	init_window(t_settings settings)
{
	t_view	view;
	t_mouse	mouse;

	view.mlx = mlx_init();
	view.window = mlx_new_window(view.mlx, settings.width, settings.height, "Cub3D");
	mouse.x = -1;
	mouse.y = -1;
	mouse.pressed = 0;
	view.settings = &settings;
	view.mouse = &mouse;
	mlx_hook(view.window, 4, 1L<<2, handle_click, &view);
	mlx_hook(view.window, 5, 1L<<3, handle_click_release, &view);
	mlx_hook(view.window, 2, 1L<<0, handle_keypress, &view);
	mlx_hook(view.window, 17, 1L<<17, handle_close_button, 0);
	mlx_loop(view.mlx);
}