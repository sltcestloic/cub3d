/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:33 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/21 15:56:38 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_keyboard(t_view *view)
{
	t_keyboard	*keyboard;
	double		olddirx;
	double		oldplanex;

	keyboard = view->keyboard;
	if (keyboard->d_pressed)
	{
		olddirx = view->player->dirx;
		view->player->dirx = view->player->dirx * cos(-0.02) - view->player->diry * sin(-0.02);
		view->player->diry = olddirx * sin(-0.02) + view->player->diry * cos(-0.02);
		oldplanex = view->player->planex; 
		view->player->planex = view->player->planex * cos(-0.02) - view->player->planey * sin(-0.02);
		view->player->planey = oldplanex * sin(-0.02) + view->player->planey * cos(-0.02);
	}
	else if (keyboard->a_pressed)
	{
		olddirx = view->player->dirx;
		view->player->dirx = view->player->dirx * cos(0.02) - view->player->diry * sin(0.02);
		view->player->diry = olddirx * sin(0.02) + view->player->diry * cos(0.02);
		oldplanex = view->player->planex; 
		view->player->planex = view->player->planex * cos(0.02) - view->player->planey * sin(0.02);
		view->player->planey = oldplanex * sin(0.2) + view->player->planey * cos(0.02);
	}
}
