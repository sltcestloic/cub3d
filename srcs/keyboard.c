/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:33 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/03 14:59:21 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_camera_lr(t_view *view, int right, int mouse)
{
	double		dx_old;
	double		px_old;
	double		rot_speed;
	t_player	*player;

	rot_speed = (double)view->settings->width / 40000.0;
	if (mouse)
		rot_speed *= view->sensivity;
	printf("%f\n", rot_speed);
	player = view->player;
	if (right)
		rot_speed = -rot_speed;
	dx_old = player->dirx;
	player->dirx = player->dirx * cos(rot_speed) - player->diry * sin(rot_speed);
	player->diry = dx_old * sin(rot_speed) + player->diry * cos(rot_speed);
    px_old = player->planex;
	player->planex = player->planex * cos(rot_speed) - player->planey * sin(rot_speed);
    player->planey = px_old * sin(rot_speed) + player->planey * cos(rot_speed);
}

void	rotate_camera_ud(t_view *view, int up, int mouse)
{
	int			rot_speed;

	rot_speed = view->settings->height / 40;
	if (mouse)
		rot_speed *= view->sensivity;
	if (up && view->horizon < (view->settings->height * 2.5))
		view->horizon += rot_speed;
	else if (view->horizon > -(view->settings->height * 2.5))
		view->horizon -= rot_speed;
}

void	move_player_fb(t_view *view, int forward)
{
	double	move_speed;
	int		x;
	int		y;

	move_speed = 0.03;
	if (view->keyboard->ctrl_pressed)
		move_speed /= 2.3;
	else if (view->keyboard->shift_pressed)
		move_speed *= 1.8;
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

void	move_player_lr(t_view *view, int right)
{
	double	move_speed;
	int		x;
	int		y;

	move_speed = 0.03;
	if (view->keyboard->ctrl_pressed)
		move_speed /= 2.3;
	else if (view->keyboard->shift_pressed)
		move_speed *= 1.8;
	if (right)
	{
		x = view->player->posx + view->player->planex * move_speed;
		y = view->player->posy + view->player->planey * move_speed;
		if (view->map->content[(int)view->player->posy][x] != '1')
			view->player->posx += view->player->planex * move_speed;
		if (view->map->content[y][(int)view->player->posx] != '1')
			view->player->posy += view->player->planey * move_speed;
	}
	else
	{
		x = view->player->posx - view->player->planex * move_speed;
		y = view->player->posy - view->player->planey * move_speed;
		if (view->map->content[(int)view->player->posy][x] != '1')
			view->player->posx -= view->player->planex * move_speed;
		if (view->map->content[y][(int)view->player->posx] != '1')
			view->player->posy -= view->player->planey * move_speed;
	}
}

void	handle_keyboard(t_view *view)
{
	t_keyboard	*keyboard;

	keyboard = view->keyboard;
	if (keyboard->d_pressed)
		move_player_lr(view, 1);
	else if (keyboard->a_pressed)
		move_player_lr(view, 0);
	else if (keyboard->w_pressed)
		move_player_fb(view, 1);
	else if (keyboard->s_pressed)
		move_player_fb(view, 0);
	if (keyboard->la_pressed)
		rotate_camera_lr(view, 0, FALSE);
	else if (keyboard->ra_pressed)
		rotate_camera_lr(view, 1, FALSE);
	if (keyboard->ua_pressed)
		rotate_camera_ud(view, 1, FALSE);
	else if (keyboard->da_pressed)
		rotate_camera_ud(view, 0, FALSE);
}
