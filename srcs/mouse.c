/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:47:31 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/23 13:53:23 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	show_mouse(t_view *view)
{
	mlx_mouse_show();
	mlx_mouse_move(view->window, view->settings->width / 2,
		view->settings->height / 2);
	view->mouse->visible = TRUE;
}

void	hide_mouse(t_view *view)
{
	mlx_mouse_hide();
	mlx_mouse_move(view->window, view->settings->width / 2,
		view->settings->height / 2);
	view->mouse->visible = FALSE;
}

void	toggle_mouse(t_view *view)
{
	if (view->mouse->visible)
		hide_mouse(view);
	else
		show_mouse(view);
}