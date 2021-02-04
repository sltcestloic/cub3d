/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:14:41 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/04 15:02:42 by lbertran         ###   ########lyon.fr   */
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
		player->dirx = 1;
		player->diry = 0;
		player->planex = 0;
		player->planey = -0.66;
	}
	else if (dir == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
		player->planex = 0;
		player->planey = 0.66;
	}
}

void		set_direction(t_player *player, char dir)
{
	if (dir == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
		player->planex = 0.66;
		player->planey = 0;
	}
	else if (dir == 'N')
	{
		player->dirx = 0;
		player->diry = -1;
		player->planex = -0.66;
		player->planey = 0;
	}
	else
		set_direction2(player, dir);
}
