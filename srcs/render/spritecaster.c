/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:09:44 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/08 16:56:49 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_distances(t_view *view)
{
	int			i;
	t_sprite	sprite;

	i = 0;
	while (i < view->sprite_count)
	{
		sprite = view->sprites[i];
		sprite.distance = ((view->player->posx - sprite.pos_x) *
			(view->player->posx - sprite.pos_x) +
			(view->player->posy - sprite.pos_y) *
			(view->player->posy - sprite.pos_y));
		view->sprites[i].distance = sprite.distance;
		i++;
	}
}

void	sort_sprites(t_view *view)
{
	int 		done;
	int			i;
	t_sprite	swap;

	done = 0;
	while (done < view->sprite_count)
	{
		i = 0;
		while (i < view->sprite_count - done - 1)
		{
			if (view->sprites[i].distance > view->sprites[i + 1].distance)
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

void	do_spritecast(t_view *view)
{
	t_sprite	sprite;
	int			i;
	double		sx;
	double		sy;

	i = 0;
	calculate_distances(view);
	sort_sprites(view);
	while (i < view->sprite_count)
	{
		sprite = view->sprites[i];
		sx = sprite.pos_x - view->player->posx;
		sy = sprite.pos_y - view->player->posy;
		sprite.invdet = 1.0 / (view->player->planex * view->player->diry - view->player->dirx * view->player->planey);
		sprite.tr_x = sprite.invdet * (view->player->diry * sprite.pos_x - view->player->dirx * sprite.pos_y);
		sprite.tr_y = sprite.invdet * (-view->player->planey * sprite.pos_x + view->player->planex * sprite.pos_y);
		sprite.screen_x = (int)view->settings->width / 2 * (1 + sprite.tr_x / sprite.tr_y);
		sprite.height = abs((int)(view->settings->height / sprite.tr_y));
		sprite.draw_start_y = -sprite.height / 2 + view->settings->height / 2;
		sprite.draw_end_y = sprite.height / 2 + view->settings->height / 2;
		sprite.width = abs((int)(view->settings->height / sprite.tr_y));
		sprite.draw_start_x = -sprite.width / 2 + sprite.screen_x;
		sprite.draw_end_x = sprite.width / 2 + sprite.screen_x;
		i++;
	}
}