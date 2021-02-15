/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/15 13:00:28 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			parse_line(char *line, t_view *view)
{
	char	**split;

	if (line[0] == 'R')
		return (parse_resolution(line, view->settings));
	else if (line[0] == 'F' || line[0] == 'C')
		return (parse_color(line, view->settings, line[0] == 'F'));
	split = ft_split(line, ' ');
	if (!is_valid_texture_entry(split[0]))
		return (print_error_exit("Invalid texture line in config.", 1));
	return (parse_texture(split, view));
}

int			is_empty(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (TRUE);
	while (line[i])
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int			parse_config(int fd, t_map *map, t_view *view)
{
	char	*line;
	int		ret;

	view->map = map;
	while ((ret = ft_get_next_line(fd, &line)) >= 0)
	{
		if (is_empty(line) && ret)
			continue ;
		if (ft_isalpha(line[0]))
		{
			if (parse_line(line, view) == ERROR)
				return (ERROR);
		}
		else if (!is_empty(line))
			if (parse_map_line(line, view) == ERROR)
				return (ERROR);
		if (ret == 0)
			break ;
	}
	view->animation = 0;
	validate_map(map, view->player);
	if (!(view->z_buffer = malloc(sizeof(double) * view->settings->width)))
		return (print_error_exit("Failed to malloc z buffer.", 1));
	close(fd);
	return (validate_settings(view->settings, view->player));
}
