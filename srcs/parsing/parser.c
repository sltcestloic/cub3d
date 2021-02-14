/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/14 14:27:00 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_settings(t_settings *settings, t_player *player)
{
	if (settings->north_texture.img == NULL)
		return (print_error("North texture not specified in .cub file"));
	if (settings->south_texture.img == NULL)
		return (print_error("South texture not specified in .cub file"));
	if (settings->east_texture.img == NULL)
		return (print_error("East texture not specified in .cub file."));
	if (settings->west_texture.img == NULL)
		return (print_error("West texture not specified in .cub file."));
	if (settings->sprite_texture[SPRITE_DEFAULT].img == NULL)
		return (print_error("Default sprite texture not specified \
		in .cub file."));
	if (settings->ground_color == 0)
		return (print_error("Ground color not specified in .cub file."));
	if (settings->sky_color == 0)
		return (print_error("Sky color not specified in .cub file."));
	if (settings->width == 0)
		return (print_error("Resolution width not specified in .cub file."));
	if (settings->height == 0)
		return (print_error("Resolution height not specified in .cub file."));
	if (player->pos_x == -1)
		return (print_error("No player in map."));
	return (SUCCESS);
}

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
