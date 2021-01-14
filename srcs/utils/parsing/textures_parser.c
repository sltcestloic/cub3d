/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:21:01 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/14 11:48:58 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int		validate_texture(char *texture)
{
	int		fd;

	fd = open(texture, O_RDONLY);
	close(fd);
	if (fd == -1)
		return (print_error("At least one texture is invalid in config."));
	return (SUCCESS);
}

static int		parse_texture2(char **split, t_settings *settings)
{
	if (ft_strcmp(split[0], "WE") == 0)
	{
		settings->west_texture = split[1];
		free_all(split);
		if (!validate_texture(settings->west_texture))
			return (ERROR);
	}
	else if (ft_strcmp(split[0], "S") == 0)
	{
		settings->sprite_texture = split[1];
		free_all(split);
		if (!validate_texture(settings->sprite_texture))
			return (ERROR);
	}
}

int				parse_texture(char **split, t_settings *settings)
{
	if (ft_strcmp(split[0], "NO") == 0)
	{
		settings->north_texture = split[1];
		free_all(split);
		if (!validate_texture(settings->north_texture))
			return (ERROR);
	}
	else if (ft_strcmp(split[0], "SO") == 0)
	{
		settings->south_texture = split[1];
		free_all(split);
		if (!validate_texture(settings->south_texture))
			return (ERROR);
	}
	else if (ft_strcmp(split[0], "EA") == 0)
	{
		settings->east_texture = split[1];
		free_all(split);
		if (!validate_texture(settings->east_texture))
			return (ERROR);
	}
	return (parse_texture2(split, settings));
}
