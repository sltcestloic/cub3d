/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:36:06 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/10 14:27:44 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_keyboard(t_view *view)
{
	t_keyboard	*keyboard;

	keyboard = view->keyboard;
	if (keyboard->d_pressed && !keyboard->a_pressed)
		move_player_lr(view, 1);
	else if (keyboard->a_pressed && !keyboard->d_pressed)
		move_player_lr(view, 0);
	else if (keyboard->w_pressed && !keyboard->s_pressed)
		move_player_fb(view, 1);
	else if (keyboard->s_pressed && !keyboard->w_pressed)
		move_player_fb(view, 0);
	if (keyboard->la_pressed && !keyboard->ra_pressed)
		rotate_camera_lr(view, 0, FALSE);
	else if (keyboard->ra_pressed && !keyboard->la_pressed)
		rotate_camera_lr(view, 1, FALSE);
	if (keyboard->ua_pressed && !keyboard->da_pressed)
		rotate_camera_ud(view, 1, FALSE);
	else if (keyboard->da_pressed && !keyboard->la_pressed)
		rotate_camera_ud(view, 0, FALSE);
}
