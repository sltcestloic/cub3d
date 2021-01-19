/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:06:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 11:11:03 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		parse_resolution(char *line, t_settings *settings)
{
	char	**split;

	split = ft_split(line, ' ');
	settings->width = ft_atoi(split[1]);
	settings->height = ft_atoi(split[2]);
	free_split(split);
	if (settings->width == 0 || settings->height == 0)
	{
		print_error("Invalid width or height in .cub file.");
		return (ERROR);
	}
	return (SUCCESS);
}

int		parse_color(char *line, t_settings *settings, int ground)
{
	char	**split;
	char	**colorsplit;

	split = ft_split(line, ' ');
	colorsplit = ft_split(split[1], ',');
	free_split(split);
	if (ground)
	{
		settings->ground_color = \
		rgbint(ft_atoi(colorsplit[0]), ft_atoi(colorsplit[1]),
			ft_atoi(colorsplit[2]));
		free_split(colorsplit);
		if (settings->ground_color == 0)
			return (print_error("Invalid ground color in .cub file."));
	}
	else
	{
		settings->sky_color = \
		rgbint(ft_atoi(colorsplit[0]), ft_atoi(colorsplit[1]),
			ft_atoi(colorsplit[2]));
		free_split(colorsplit);
		if (settings->sky_color == 0)
			return (print_error("Invalid sky color in .cub file."));
	}
	return (SUCCESS);
}
