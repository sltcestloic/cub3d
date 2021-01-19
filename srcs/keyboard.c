/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:33 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 14:13:20 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_keyboard(t_view *view)
{
	t_keyboard	*keyboard;

	keyboard = view->keyboard;
	if (keyboard->w_pressed && view->circle->y > 2)
		view->circle->y--;
	if (keyboard->a_pressed && view->circle->x > 2)
		view->circle->x--;
	if (keyboard->s_pressed && view->circle->y < view->settings->height - 2)
		view->circle->y++;
	if (keyboard->d_pressed && view->circle->x < view->settings->width - 2)
		view->circle->x++;
}
