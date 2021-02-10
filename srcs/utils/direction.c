/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:14:41 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/10 15:04:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** norm split
*/

t_texture	get_texture(int direction, t_view *view)
{
	t_texture	texture;

	if (direction == NORTH)
		texture = view->settings->north_texture;
	else if (direction == SOUTH)
		texture = view->settings->south_texture;
	else if (direction == EAST)
		texture = view->settings->east_texture;
	else
		texture = view->settings->west_texture;
	return (texture);
}

static void	set_direction2(t_player *player, char dir)
{
	if (dir == 'E')
	{
		player->dir_x = 1.000001;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1.000001;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

void		set_direction(t_player *player, char dir)
{
	if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1.000001;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1.000001;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		set_direction2(player, dir);
}
