/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 10:52:14 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_settings(t_settings *settings)
{
	settings->width = 0;
	settings->height = 0;
	settings->sky_color = 0;
	settings->ground_color = 0;
	settings->north_texture = NULL;
	settings->south_texture = NULL;
	settings->east_texture = NULL;
	settings->west_texture = NULL;
	settings->sprite_texture = NULL;
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

	init_settings(&settings);
	init_map(&map);
	if (ac < 2)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
	}
	path = av[1];
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Please provide a valid file path.");
		return (FALSE);
	}
	if (parse_config(fd, &settings, &map) == SUCCESS)
		init_window(settings);
	return (TRUE);
}
