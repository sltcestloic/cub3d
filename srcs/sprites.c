/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:23:49 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/16 13:17:29 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	reset_sprites(t_view *view)
{
	int	i;

	i = 0;
	while (i < view->sprite_count)
		view->sprites[i++].visible = TRUE;
}

void	calculate_distances(t_view *view)
{
	int			i;
	t_sprite	sprite;

	i = 0;
	while (i < view->sprite_count)
	{
		sprite = view->sprites[i];
		sprite.distance = ((view->player->pos_x - sprite.pos_x)
				* (view->player->pos_x - sprite.pos_x)
				+ (view->player->pos_y - sprite.pos_y)
				* (view->player->pos_y - sprite.pos_y));
		view->sprites[i].distance = sprite.distance;
		i++;
	}
}

void	sort_sprites(t_view *view)
{
	int			done;
	int			i;
	t_sprite	swap;

	done = 0;
	while (done < view->sprite_count)
	{
		i = 0;
		while (i < view->sprite_count - done - 1)
		{
			if (view->sprites[i].distance < view->sprites[i + 1].distance)
			{
				swap = view->sprites[i];
				view->sprites[i] = view->sprites[i + 1];
				view->sprites[i + 1] = swap;
			}
			++i;
		}
		++done;
	}
}
