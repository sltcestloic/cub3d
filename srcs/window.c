/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:57:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/15 16:33:19 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		handle_click(int button, int x, int y)
{
	printf("%d %d %d\n", button, x, y);
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

void	init_window(t_settings settings)
{
	t_view	view;

	view.mlx = mlx_init();
	view.window = mlx_new_window(view.mlx, settings.width, settings.height, "Cub3D");
	mlx_hook(view.window, 4, 1L<<2, handle_click, 0);
	mlx_hook(view.window, 2, 1L<<0, handle_keypress, &view);
	mlx_loop(view.mlx);
}