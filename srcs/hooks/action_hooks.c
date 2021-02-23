/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:27:01 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/23 13:50:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		handle_click(int button, int x, int y, t_view *view)
{
	(void)x;
	(void)y;
	if (button == 1)
		view->mouse->pressed = 1;
	return (0);
}

int		handle_click_release(int button, int x, int y, t_view *view)
{
	(void)x;
	(void)y;
	if (button == 1)
		view->mouse->pressed = 0;
	return (0);
}

int		handle_close_button(void)
{
	exit(0);
	return (0);
}

int		handle_key_press(int keycode, t_view *view)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 13)
		view->keyboard->w_pressed = TRUE;
	else if (keycode == 0)
		view->keyboard->a_pressed = TRUE;
	else if (keycode == 1)
		view->keyboard->s_pressed = TRUE;
	else if (keycode == 2)
		view->keyboard->d_pressed = TRUE;
	if (keycode == 123)
		view->keyboard->la_pressed = TRUE;
	else if (keycode == 124)
		view->keyboard->ra_pressed = TRUE;
	if (keycode == 125)
		view->keyboard->da_pressed = TRUE;
	else if (keycode == 126)
		view->keyboard->ua_pressed = TRUE;
	if (keycode == 257)
		view->keyboard->shift_pressed = TRUE;
	else if (keycode == 256)
		view->keyboard->ctrl_pressed = TRUE;
	else if (keycode == 49)
		player_jump(view);
	else if (keycode == 48)
		toggle_mouse(view);
	return (0);
}

int		handle_key_release(int keycode, t_view *view)
{
	if (keycode == 13)
		view->keyboard->w_pressed = FALSE;
	else if (keycode == 0)
		view->keyboard->a_pressed = FALSE;
	else if (keycode == 1)
		view->keyboard->s_pressed = FALSE;
	else if (keycode == 2)
		view->keyboard->d_pressed = FALSE;
	if (keycode == 123)
		view->keyboard->la_pressed = FALSE;
	else if (keycode == 124)
		view->keyboard->ra_pressed = FALSE;
	if (keycode == 125)
		view->keyboard->da_pressed = FALSE;
	else if (keycode == 126)
		view->keyboard->ua_pressed = FALSE;
	if (keycode == 257)
		view->keyboard->shift_pressed = FALSE;
	else if (keycode == 256)
		view->keyboard->ctrl_pressed = FALSE;
	return (0);
}
