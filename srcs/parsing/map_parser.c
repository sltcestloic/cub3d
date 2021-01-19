/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 11:10:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** 
*/

int				validate_map(t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map->content[y])
	{
		x = 0;
		while (map->content[y][x])
		{
			if ((y == 0 || (int)y == map->lines - 1) && map->content[y][x] != '1'
				&& map->content[y][x] != ' ')
				return (FALSE);
			if (y < (size_t)map->lines - 1 && map->content[y + 1][x] == ' ' &&
				map->content[y][x] != '1' && map->content[y][x] != ' ')
					return (FALSE);
			if (y > 0 && map->content[y - 1][x] == ' ' &&
				map->content[y][x] != '1' && map->content[y][x] != ' ')
					return (FALSE);
			x++;
		}
		y++;
	}
	return (TRUE);
}

static int		validate_map_line(char *line, t_map *map)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!line[i] || line[i] != '1')
		return (FALSE);
	while (is_valid_map_char(line[i]) || line[i] == ' ')
	{
		if (is_valid_player_char(line[i]))
		{
			if (map->px == -1)
			{
				map->px = i;
				map->py = map->lines;
			}
			else
				return (print_error("More than one player in map.") + 1);
		}
		i++;
	}
	if (line[i - 1] != '1')
		return (FALSE);
	return (TRUE);
}

void			copy_content(char **old, char **new)
{
	size_t	i;

	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = 0;
	free_split(old);
}

int				parse_map_line(char *line, t_map *map)
{
	char	**new_content;

	if (!validate_map_line(line, map))
	{
		print_error("Invalid map line.");
		printf("Invalid line: #%d (%s)\n", map->lines + 1, line);
		return (ERROR);
	}
	if (!(new_content = malloc(sizeof(char *) * (map->lines + 2))))
	{
		if (map->content)
			free_split(map->content);
		return (ERROR);
	}
	if (map->content)
		copy_content(map->content, new_content);
	new_content[map->lines] = line;
	new_content[++map->lines] = 0;
	map->content = new_content;
	return (SUCCESS);
}
