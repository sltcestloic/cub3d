/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/14 15:36:37 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** 
*/

int				is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W');
}

static int		validate_map_line(char *line)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!line[i] || line[i] != '1')
		return (FALSE);
	while (is_valid_map_char(line[i]))
		i++;
	return (line[i - 1] == '1');
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
		printf("Invalid line: %s\n", line);
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
	map->lines++;
	new_content[map->lines] = 0;
	map->content = new_content;
	return (SUCCESS);
}
