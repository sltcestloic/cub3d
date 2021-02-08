/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:18:48 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/08 16:08:31 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_sprite(int x, int y, t_view *view)
{
	t_sprite	sprite;

	sprite.pos_x = x + 0.5;
	sprite.pos_y = y + 0.5;
	sprite.order = view->sprite_count;
	printf("x: %f y: %f order: %d\n", sprite.pos_x, sprite.pos_y, sprite.order);
	view->sprites[sprite.order] = sprite;
	view->sprite_count++;
}
