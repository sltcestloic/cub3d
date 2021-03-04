/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:14:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/03 12:59:07 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void			copy_content(char **old, char **next, int mlc)
{
	size_t	i;

	i = 0;
	while (old[i])
	{
		if (!(next[i] = malloc(sizeof(char) * (mlc + 1))))
			return ;
		ft_strlcpy(next[i], old[i], ft_strlen(old[i]) + 1);
		i++;
	}
	next[i] = 0;
}

int				parse_map_line(char *line, t_view *view)
{
	char	**new_content;

	if (!validate_map_line(line, view))
	{
		print_error("Invalid map line.");
		printf("Invalid line: #%d (%s)\n", view->map->lines + 1, line);
		return (ERROR);
	}
	if (!(new_content = malloc(sizeof(char *) * (view->map->lines + 2))))
	{
		if (view->map->content)
			free_split(view->map->content);
		return (ERROR);
	}
	if (view->map->longest < (int)ft_strlen(line))
		view->map->longest = ft_strlen(line);
	if (view->map->content)
	{
		copy_content(view->map->content, new_content, view->map->longest);
		free_split(view->map->content);
	}
	new_content[view->map->lines] = line;
	new_content[++view->map->lines] = 0;
	view->map->content = new_content;
	return (SUCCESS);
}
