/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/01 13:14:52 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			parse_line(char *line, t_view *view)
{
	char	**split;

	split = ft_split(line, ' ');
	free(line);
	if (ft_strcmp(split[0], "R") == 0)
		return (parse_resolution(split, view->settings));
	else if (ft_strcmp(split[0], "F") == 0 || ft_strcmp(split[0], "C") == 0)
	{
		return (parse_color(split, view->settings,
			ft_strcmp(split[0], "F") == 0));
	}
	if (!is_valid_texture_entry(split[0]))
	{
		free_split(split);
		return (print_error_exit("Invalid line in config.", 1));
	}
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

int			read_config(int fd, t_view *view)
{
	int		ret;
	char	*line;

	line = NULL;
	parse_static_textures(view);
	while ((ret = ft_get_next_line(fd, &line)) >= 0)
	{
		if (is_empty(line) && ret)
		{
			free(line);
			continue ;
		}
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
	free(line);
	return (ret == -1 ? print_error("Invalid .cub file.") : SUCCESS);
}

int			parse_config(int fd, t_map *map, t_view *view)
{
	view->map = map;
	if (read_config(fd, view) == ERROR)
		return (ERROR);
	view->animation = 0;
	validate_map(map, view->player);
	if (!(view->z_buffer = malloc(sizeof(double) * view->settings->width)))
		return (print_error_exit("Failed to malloc z buffer.", 1));
	close(fd);
	return (validate_settings(view->settings, view->player));
}
