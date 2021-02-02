/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/02 13:03:52 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** 
*/

void			run_map_validation(t_map *map, int x, int y)
{
	printf("validating %d %d\n", x, y);
	if (map->content_copy[y][x] != '1')
	{
		if (x == 0 || y == 0 || x == map->longest - 1 || y == map->lines - 1)
			print_error_exit("Invalid map. (Check #1)", 1);
		if (map->content_copy[y][x] == ' ')
			print_error_exit("Invalid map. (Check #2)", 1);
		map->content_copy[y][x] = '1';
		run_map_validation(map, x + 1, y);
		run_map_validation(map, x + 1, y + 1);
		run_map_validation(map, x + 1, y - 1);
		run_map_validation(map, x, y + 1);
		run_map_validation(map, x, y - 1);
		run_map_validation(map, x - 1, y);
		run_map_validation(map, x - 1, y + 1);
		run_map_validation(map, x - 1, y - 1);
	}
}

void			copy_content(char **old, char **new, int mlc)
{
	size_t	i;

	i = 0;
	while (old[i])
	{
		if (!(new[i] = malloc(sizeof(char) * mlc)))
			return ;
		ft_bzero(new[i], mlc);
		ft_strlcpy(new[i], old[i], ft_strlen(old[i]) + 1);
		i++;
	}
	new[i] = 0;
}

int				validate_map(t_map *map)
{
	int		i;

	i = 0;
	copy_content(map->content, map->content_copy, map->longest);
	while (map->content_copy[1][i])
	{
		if (map->content_copy[1][i] != ' ' && map->content_copy[1][i] != '1')
		{
			run_map_validation(map, i, 1);
			break ;
		}
		i++;
	}
	return (TRUE);
}

static int		validate_map_line(char *line, t_map *map, t_player *player)
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
			if (player->posx == -1)
			{
				player->posx = i;
				player->posy = map->lines;
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

int				parse_map_line(char *line, t_map *map, t_player *player)
{
	char	**new_content;
	if (!validate_map_line(line, map, player))
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
	if (map->longest < (int)ft_strlen(line))
		map->longest = ft_strlen(line);
	if (map->content)
	{
		copy_content(map->content, new_content, map->longest);
		free_split(map->content);
	}
	new_content[map->lines] = line;
	new_content[++map->lines] = 0;
	map->content = new_content;
	return (SUCCESS);
}
