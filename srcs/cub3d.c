/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/03 14:47:50 by lbertran         ###   ########lyon.fr   */
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
	settings->sprite_texture.img = NULL;
}

static void	init_map(t_map *map)
{
	map->content = NULL;
	map->lines = 0;
	map->longest = 0;
}

static void	init_player(t_player *player)
{
	player->dirx = -1;
	player->diry = 0;
	player->planex = 0;
	player->planey = 0.66;
	player->posx = -1;
	player->posy = 0;
}

int			validate_args(int ac, char **av, int *fd)
{
	if (ac < 2 || ac > 3)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
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
	if (!validate_args(ac, av, &fd))
		return (FALSE);
	view.mlx = mlx_init();
	view.player = &player;
	view.settings = &settings;
	view.horizon = 0;
	view.sensivity = 0.54;
	if (parse_config(fd, &map, &view) == SUCCESS)
		init_window(settings, view);
	return (TRUE);
}
