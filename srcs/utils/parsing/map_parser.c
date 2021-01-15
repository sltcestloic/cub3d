/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/15 10:08:02 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** 
*/

int				validate_map_columns(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
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
		if (!map->content[y][x + 1])
		{
			y++;
			x = -1;
		}
		if (y == (size_t)map->lines - 1)
			break ;
		x++;
	}
	return (TRUE);
}

static int		validate_map_line(char *line)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!line[i] || line[i] != '1')
		return (FALSE);
	while (is_valid_map_char(line[i]) || line[i] == ' ')
		i++;
	if (line[i - 1] != '1')
		return (FALSE);
	i = 0;
	while (line[i])
	{
		if (ft_iswhitespace(line[i]))
		{
			i++;
			continue;
		}
		if (i > 0 && line[i - 1] == ' ' && line[i] != '1' && line[i] != ' ')
			return (FALSE);
		if (line[i + 1] && line[i + 1] == ' ' && line[i] != '1' &&
			line[i] != ' ')
			return (FALSE);
		i++;
	}
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

	if (!validate_map_line(line))
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
