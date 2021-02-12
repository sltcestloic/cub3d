/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:18:31 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/12 14:38:27 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reset_sprites(t_view *view)
{
	int	i;

	i = 0;
	while (i < view->sprite_count)
		view->sprites[i++].visible = TRUE;
}

int		handle_death(t_view *view)
{
	t_player	*player;

	player = view->player;
	player->pos_y = player->spawn_py;
	player->pos_x = player->spawn_px;
	player->plane_x = player->spawn_plx;
	player->plane_y = player->spawn_ply;
	player->dir_x = player->spawn_dx;
	player->dir_y = player->spawn_dy;
	player->health = MAX_HEALTH;
	player->move_count = 0;
	return (FALSE);
}

void	handle_win(t_view *view)
{
	int		time;
	int		minutes;
	int		secondes;

	time = (current_millis() - view->start_timestamp) / 1000;
	if (time > 60)
	{
		secondes = time % 60;
		minutes = time / 60;
	}
	else
	{
		minutes = 0;
		secondes = time;
	}
	printf("t'as win bravo\n");
	printf("Tu as mit %d minutes et %d secondes", minutes, secondes);
	exit(0);
}

int		handle_sprite_collision(t_view *view, t_sprite *sprite)
{
	if (sprite->type == SPRITE_HEALTH)
	{
		if (view->player->health == MAX_HEALTH)
			return (FALSE);
		view->player->health++;
	}
	else if (sprite->type == SPRITE_TRAP)
	{
		view->player->health--;
		if (view->player->health == 0)
		{
			handle_death(view);
			reset_sprites(view);
			return (FALSE);
		}
	}
	else if (sprite->type == SPRITE_CUP)
		handle_win(view);
	sprite->visible = FALSE;
	return (FALSE);
}

int		collision(t_view *view, double y, double x)
{
	int			i;
	t_sprite	*sprite;
	double		distance;

	i = 0;
	while (i < view->sprite_count)
	{
		sprite = &view->sprites[i];
		distance = ((x - sprite->pos_x) *
			(x - sprite->pos_x) +
			(y - sprite->pos_y) *
			(y - sprite->pos_y));
		if (distance < 0.2 && sprite->visible && view->player->move_count > 0)
		{
			if (sprite->type != SPRITE_DEFAULT)
				return (handle_sprite_collision(view, sprite));
			return (TRUE);
		}
		i++;
	}
	return (view->map->content[(int)y][(int)x] == '1');
}
