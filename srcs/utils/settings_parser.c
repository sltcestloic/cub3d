/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:06:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 16:52:21 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		parse_resolution(char *line, t_settings *settings)
{
	char	**split;

	split = ft_split(line, ' ');
	settings->width = ft_atoi(split[1]);
	settings->height = ft_atoi(split[2]);
	if (settings->width == 0 || settings->height == 0)
	{
		print_error("Invalid width or height in config.");
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
	if (ground)
		settings->ground_color = \
		rgbint(ft_atoi(colorsplit[0]), ft_atoi(colorsplit[1]), ft_atoi(colorsplit[2]));
	else
		settings->sky_color = \
		rgbint(ft_atoi(colorsplit[0]), ft_atoi(colorsplit[1]), ft_atoi(colorsplit[2]));
	if (settings->ground_color == 0 || settings->sky_color == 0)
	{
		print_error("Invalid sky or ground color in config.");
		return (ERROR);
	}
	return (SUCCESS);
}