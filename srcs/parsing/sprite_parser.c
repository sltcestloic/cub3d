/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:18:48 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/12 14:07:13 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_sprite(int x, int y, t_view *view, int type)
{
	t_sprite	sprite;

	if (view->sprite_count == 50)
		return ;
	sprite.pos_x = x + 0.5;
	sprite.pos_y = y + 0.5;
	sprite.type = type - 2;
	sprite.order = view->sprite_count;
	sprite.visible = TRUE;
	view->sprites[sprite.order] = sprite;
	view->sprite_count++;
}
