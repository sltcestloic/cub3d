/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:09:44 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/09 15:15:56 by lbertran         ###   ########lyon.fr   */
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

void	spritecast(t_view *view, t_sprite *sprite, t_player *player)
{
	double	sx;
	double	sy;

	sx = sprite->pos_x - player->posx;
	sy = sprite->pos_y - player->posy;
	sprite->invdet = 1.0 / (player->planex * player->diry -
		player->dirx * player->planey);
	sprite->tr_x = sprite->invdet * (player->diry * sx - player->dirx * sy);
	sprite->tr_y = sprite->invdet * (-player->planey * sx +
		player->planex * sy);
	sprite->screen_x = (int)view->settings->width / 2 *
		(1 + sprite->tr_x / sprite->tr_y);
	sprite->height = abs((int)(view->settings->height / sprite->tr_y));
	sprite->draw_start_y = -sprite->height / 2 + view->settings->height / 2;
	sprite->draw_start_y += view->horizon;
	sprite->draw_end_y = sprite->height / 2 + view->settings->height / 2;
	sprite->draw_end_y += view->horizon;
	sprite->width = abs((int)(view->settings->height / sprite->tr_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen_x;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen_x;
	if (view->keyboard->ctrl_pressed)
	{
		sprite->draw_start_y += 50;
		sprite->draw_end_y += 50;
	}
}

void	do_spritecast(t_view *view)
{
	int			i;
	t_sprite	sprite;

	i = 0;
	calculate_distances(view);
	sort_sprites(view);
	while (i < view->sprite_count)
	{
		sprite = view->sprites[i];
		spritecast(view, &sprite, view->player);
		draw_sprite(view, &sprite);
		i++;
	}
}
