/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/16 13:51:41 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_line(char *line, t_view *view)
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

void	handle_empty_line(t_view *view, char *line)
{
	if (!view->map->parsed && view->map->content != NULL)
		view->map->parsed = TRUE;
	free(line);
}

int	read_line(t_view *view, char *line)
{
	if (ft_isalpha(line[0]))
	{
		if (parse_line(line, view) == ERROR)
			return (ERROR);
	}
	else if (view->map->parsed)
		return (print_error_exit("Invalid map.", 1));
	else if (parse_map_line(line, view) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	read_config(int fd, t_view *view)
{
	int		ret;
	char	*line;

	while (TRUE)
	{
		ret = ft_get_next_line(fd, &line);
		if (is_empty(line))
		{
			handle_empty_line(view, line);
			if (ret)
				continue ;
			break ;
		}
		if (read_line(view, line) == ERROR)
			return (ERROR);
		if (ret == 0)
			break ;
	}
	if (ret == -1)
		return (print_error_exit("Invalid .cub file.", 1));
	return (SUCCESS);
}

int	parse_config(int fd, t_map *map, t_view *view)
{
	view->map = map;
	parse_static_textures(view);
	if (read_config(fd, view) == ERROR)
		return (ERROR);
	view->animation = 0;
	validate_map(map, view->player);
	view->z_buffer = malloc(sizeof(double) * view->settings->width);
	if (!view->z_buffer)
		return (print_error_exit("Failed to malloc z buffer.", 1));
	close(fd);
	return (validate_settings(view->settings, view->player));
}
