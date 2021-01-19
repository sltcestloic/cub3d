/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 11:11:00 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_settings(t_settings *settings, t_map *map)
{
	if (settings->north_texture == NULL)
		return (print_error("North texture not specified in .cub file"));
	if (settings->south_texture == NULL)
		return (print_error("South texture not specified in .cub file"));
	if (settings->east_texture == NULL)
		return (print_error("East texture not specified in .cub file."));
	if (settings->west_texture == NULL)
		return (print_error("West texture not specified in .cub file."));
	if (settings->sprite_texture == NULL)
		return (print_error("Sprite texture not specified in .cub file."));
	if (settings->ground_color == 0)
		return (print_error("Ground color not specified in .cub file."));
	if (settings->sky_color == 0)
		return (print_error("Sky color not specified in .cub file."));
	if (settings->width == 0)
		return (print_error("Resolution width not specified in .cub file."));
	if (settings->height == 0)
		return (print_error("Resolution height not specified in .cub file."));
	if (map->px == -1)
		return (print_error("No player in map."));
	return (SUCCESS);
}

int			parse_line(char *line, t_settings *settings)
{
	char	**split;

	if (line[0] == 'R')
		return (parse_resolution(line, settings));
	else if (line[0] == 'F' || line[0] == 'C')
		return (parse_color(line, settings, line[0] == 'F'));
	split = ft_split(line, ' ');
	if (ft_strcmp(split[0], "SO") == 0 || ft_strcmp(split[0], "NO")
		|| ft_strcmp(split[0], "EA") || ft_strcmp(split[0], "WE")
		|| ft_strcmp(split[0], "S"))
		return (parse_texture(split, settings));
	return (ERROR);
}

int			parse_config(int fd, t_settings *settings, t_map *map)
{
	char	*line;
	int		ret;
	
	while ((ret = ft_get_next_line(fd, &line)) >= 0)
	{
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_isalpha(line[0]))
		{
			if (parse_line(line, settings) == ERROR)
				return (ERROR);
		}
		else
			if (parse_map_line(line, map) == ERROR)
				return (ERROR);
		if (ret == 0)
			break ;
	}
	if (!validate_map(map))
		return (print_error("Invalid map.") + 1);
	for (int i = 0; map->content[i]; i++)
		printf("%s\n", map->content[i]);
	close(fd);
	return (validate_settings(settings, map));
}
