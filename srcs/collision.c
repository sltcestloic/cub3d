/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:18:31 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/09 15:50:20 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	collision(t_view *view, double y, double x)
{
	int			i;
	t_sprite	sprite;
	double		distance;

	i = 0;
	while (i < view->sprite_count)
	{
		sprite = view->sprites[i];
		distance = ((x - sprite.pos_x) *
			(x - sprite.pos_x) +
			(y - sprite.pos_y) *
			(y - sprite.pos_y));
		if (distance < 0.1)
		{
			return (TRUE);
		}
		i++;
	}
	return (view->map->content[(int)y][(int)x] == '1');
}
