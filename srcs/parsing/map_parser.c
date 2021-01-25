/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/25 10:00:16 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** 
*/

int				check_pos(t_map *map, int x, int y)
{
	int	len;
	int	height;

	len = (int)ft_strlen(map->content[y]);
	height = map->lines;
	if (x == 0 || x == len - 1)
		return (TRUE);
	if (y == 0 || y == height - 1)
		return (TRUE);
	if (y == 1 && (map->content[y - 1][x] != '1' ||
		map->content[y - 1][x - 1] != '1' || map->content[y - 1][x + 1] != '1'))
		return (print_error("Invalid map. (check 1)"));
	if (x == 1 && (map->content[y][x - 1] != '1' ||
		map->content[y + 1][x - 1] != '1' || map->content[y - 1][x - 1] != '1'))
		return (print_error("Invalid map. (check 2)"));
	if (x == len - 2 && (map->content[y][x + 1] != '1' ||
		map->content[y + 1][x + 1] != '1' || map->content[y - 1][x + 1] != '1'))
		return (print_error("Invalid map. (check 3)"));
	if (y == height - 2 && (map->content[y + 1][x] != '1' ||
		map->content[y + 1][x - 1] != '1' || map->content[y + 1][x + 1] != '1'))
		return (print_error("Invalid map. (check 4)"));
	if (!is_valid_map_char(map->content[y][x + 1])
		|| !is_valid_map_char(map->content[y][x - 1])
		|| !is_valid_map_char(map->content[y + 1][x])
		|| !is_valid_map_char(map->content[y - 1][x])
		|| !is_valid_map_char(map->content[y + 1][x + 1])
		|| !is_valid_map_char(map->content[y + 1][x - 1])
		|| !is_valid_map_char(map->content[y - 1][x + 1])
		|| !is_valid_map_char(map->content[y - 1][x - 1]))
		return (print_error("Invalid map. (check 5)"));
	return (TRUE);
}

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
			if (map->content[y][x] != '1' && map->content[y][x] != ' ')
				if (check_pos(map, x, y) == ERROR)
					return (FALSE);
			x++;
		}
		y++;
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

void			copy_content(char **old, char **new, int mlc)
{
	size_t	i;

	i = 0;
	printf("malloc %d\n", mlc);
	while (old[i])
	{
		if (!(new[i] = malloc(sizeof(char) * mlc)))
			return ;
		ft_bzero(new[i], mlc);
		printf("%zu\n", ft_strlen(old[i]));
		ft_strlcpy(new[i], old[i], ft_strlen(old[i]) + 1);
		i++;
	}
	new[i] = 0;
	free_split(old);
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
		copy_content(map->content, new_content, map->longest);
	new_content[map->lines] = line;
	new_content[++map->lines] = 0;
	map->content = new_content;
	return (SUCCESS);
}
