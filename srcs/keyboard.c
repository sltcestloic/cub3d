/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:33 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/02 12:49:35 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_camera(t_view *view, int side)
{
	(void)view;
	(void)side;
}

void	move_player(t_view *view, int forward)
{
	double	move_speed;
	int		x;
	int		y;

	move_speed = 0.03;
	if (forward)
	{
		x = view->player->posx + view->player->dirx * move_speed;
		y = view->player->posy + view->player->diry * move_speed;
		if (view->map->content[(int)view->player->posy][x] != '1')
			view->player->posx += view->player->dirx * move_speed;
		if (view->map->content[y][(int)view->player->posx] != '1')
			view->player->posy += view->player->diry * move_speed;
	}
	else
	{
		x = view->player->posx - view->player->dirx * move_speed;
		y = view->player->posy - view->player->diry * move_speed;
		if (view->map->content[(int)view->player->posy][x] != '1')
			view->player->posx -= view->player->dirx * move_speed;
		if (view->map->content[y][(int)view->player->posx] != '1')
			view->player->posy -= view->player->diry * move_speed;
	}
}

void	handle_keyboard(t_view *view)
{
	t_keyboard	*keyboard;

	keyboard = view->keyboard;
	if (keyboard->d_pressed)
		rotate_camera(view, FALSE);
	else if (keyboard->a_pressed)
		rotate_camera(view, TRUE);
	else if (keyboard->w_pressed)
		move_player(view, 1);
	else if (keyboard->s_pressed)
		move_player(view, 0);
}
