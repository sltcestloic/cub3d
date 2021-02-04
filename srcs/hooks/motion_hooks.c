/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:56:05 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/04 16:29:22 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse_motion(int x, int y, t_view *view)
{
	if (x > view->settings->width || x < 0 || y < 0 ||
		y > view->settings->height)
	{
		mlx_mouse_move(view->window, view->settings->width / 2,
		view->settings->height / 2);
		return (0);
	}
	if (x > view->settings->width / 2)
		rotate_camera_lr(view, TRUE, abs(x - view->settings->width / 2));
	else if (x < view->settings->width / 2)
		rotate_camera_lr(view, FALSE, abs(x - view->settings->width / 2));
	if (y > view->settings->height / 2)
		rotate_camera_ud(view, FALSE, abs(y - view->settings->height / 2));
	else if (y < view->settings->height / 2)
		rotate_camera_ud(view, TRUE, abs(y - view->settings->height / 2));
	mlx_mouse_move(view->window, view->settings->width / 2,
		view->settings->height / 2);
	return (0);
}
