/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:33 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/19 11:10:46 by lbertran         ###   ########lyon.fr   */
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
	if (mouse > 0)
	{
		rot_speed *= 0.54;
		rot_speed *= (mouse * 100 / 500);
	}
	if (view->keyboard->shift_pressed && !mouse)
		rot_speed *= 2;
	player = view->player;
	if (!right)
		rot_speed = -rot_speed;
	dx_old = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y *
		sin(rot_speed);
	player->dir_y = dx_old * sin(rot_speed) + player->dir_y * cos(rot_speed);
	px_old = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y *
		sin(rot_speed);
	player->plane_y = px_old * sin(rot_speed) + player->plane_y *
		cos(rot_speed);
}

void	rotate_camera_ud(t_view *view, int up, int mouse)
{
	int			rot_speed;

	rot_speed = view->settings->height / 40;
	if (view->keyboard->shift_pressed)
		rot_speed *= 2;
	if (mouse > 0)
	{
		rot_speed *= 0.54;
		rot_speed *= (mouse * 100 / 500);
	}
	if (up && view->horizon < (view->settings->height * 2.5))
		view->horizon += rot_speed;
	else if (view->horizon > -(view->settings->height * 2.5))
		view->horizon -= rot_speed;
}

double	get_speed(t_view *view, int forward)
{
	double	base_speed;

	base_speed = 0.03;
	if (view->keyboard->ctrl_pressed)
		base_speed /= 2.3;
	else if (view->keyboard->shift_pressed && forward)
		base_speed *= 1.8;
	return (base_speed);
}

void	move_player_fb(t_view *view, int forward)
{
	double	move_speed;
	double	x;
	double	y;

	move_speed = get_speed(view, forward);
	if (forward)
	{
		x = view->player->pos_x + view->player->dir_x * move_speed;
		y = view->player->pos_y + view->player->dir_y * move_speed;
		if (!collision(view, view->player->pos_y, x))
			view->player->pos_x += view->player->dir_x * move_speed;
		if (!collision(view, y, view->player->pos_x))
			view->player->pos_y += view->player->dir_y * move_speed;
	}
	else
	{
		x = view->player->pos_x - view->player->dir_x * move_speed;
		y = view->player->pos_y - view->player->dir_y * move_speed;
		if (!collision(view, view->player->pos_y, x))
			view->player->pos_x -= view->player->dir_x * move_speed;
		if (!collision(view, y, view->player->pos_x))
			view->player->pos_y -= view->player->dir_y * move_speed;
	}
	view->player->move_count++;
}

void	move_player_lr(t_view *view, int right)
{
	double	move_speed;
	double	x;
	double	y;

	move_speed = get_speed(view, FALSE);
	if (!right)
	{
		x = view->player->pos_x + view->player->plane_x * move_speed;
		y = view->player->pos_y + view->player->plane_y * move_speed;
		if (!collision(view, view->player->pos_y, x))
			view->player->pos_x += view->player->plane_x * move_speed;
		if (!collision(view, y, view->player->pos_x))
			view->player->pos_y += view->player->plane_y * move_speed;
	}
	else
	{
		x = view->player->pos_x - view->player->plane_x * move_speed;
		y = view->player->pos_y - view->player->plane_y * move_speed;
		if (!collision(view, view->player->pos_y, x))
			view->player->pos_x -= view->player->plane_x * move_speed;
		if (!collision(view, y, view->player->pos_x))
			view->player->pos_y -= view->player->plane_y * move_speed;
	}
	view->player->move_count++;
}
