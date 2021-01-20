/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/20 10:00:14 by lbertran         ###   ########lyon.fr   */
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
	map->px = -1;
	map->py = -1;
}

int			main(int ac, char **av)
{
	char		*path;
	int			fd;
	t_settings	settings;
	t_map		map;
	t_view		view;

	init_settings(&settings);
	init_map(&map);
	if (ac < 2)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
	}
	view.mlx = mlx_init();
	path = av[1];
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Please provide a valid file path.");
		return (FALSE);
	}
	view.settings = &settings;
	if (parse_config(fd, &map, &view) == SUCCESS)
		init_window(settings, view);
	return (TRUE);
}
