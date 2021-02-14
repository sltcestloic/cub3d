/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/14 12:54:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_settings(t_settings *settings)
{
	settings->width = 0;
	settings->height = 0;
	settings->sky_color = 0;
	settings->ground_color = 0;
	settings->north_texture.img = NULL;
	settings->south_texture.img = NULL;
	settings->east_texture.img = NULL;
	settings->west_texture.img = NULL;
	settings->sprite_texture[SPRITE_DEFAULT].img = NULL;
	settings->sprite_texture[SPRITE_HEALTH].img = NULL;
	settings->sprite_texture[SPRITE_TRAP].img = NULL;
}

static void	init_map(t_map *map)
{
	map->content = NULL;
	map->lines = 0;
	map->longest = 0;
}

static void	init_player(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->pos_x = -1;
	player->pos_y = -1;
	player->health = MAX_HEALTH;
	player->move_count = 0;
}

int				validate_args(int ac, char **av, int *fd, t_view *view)
{
	if (ac < 2 || ac > 3)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
	}
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save") != 0)
			return (print_error("Usage: ./cub3d <map path> (--save)") + 1);
		view->save = TRUE;
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
	{
		print_error("Please provide a valid file path.");
		return (FALSE);
	}
	return (TRUE);
}

int			main(int ac, char **av)
{
	int			fd;
	t_settings	settings;
	t_map		map;
	t_view		view;
	t_player	player;

	init_settings(&settings);
	init_map(&map);
	init_player(&player);
	view.save = FALSE;
	if (!validate_args(ac, av, &fd, &view))
		return (FALSE);
	view.mlx = mlx_init();
	view.player = &player;
	view.settings = &settings;
	view.horizon = 0;
	view.move_speed = 0.03;
	view.sprite_count = 0;
	view.blackout = 0;
	view.lsd = 0;
	view.finished = 0;
	view.start_timestamp = current_millis();
	if (parse_config(fd, &map, &view) == SUCCESS)
		init_window(settings, view);
	return (TRUE);
}
