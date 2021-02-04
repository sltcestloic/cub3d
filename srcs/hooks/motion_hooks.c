/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:56:05 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/04 15:27:34 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse_motion(int x, int y, t_view *view)
{
	if (x > view->settings->width / 2)
		rotate_camera_lr(view, TRUE, TRUE);
	else if (x < view->settings->width / 2)
		rotate_camera_lr(view, FALSE, TRUE);
	if (y > view->settings->height / 2)
		rotate_camera_ud(view, FALSE, TRUE);
	else if (y < view->settings->height / 2)
		rotate_camera_ud(view, TRUE, TRUE);
	mlx_mouse_move(view->window, view->settings->width / 2,
		view->settings->height / 2);
	return (0);
}
