/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 17:15:23 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_settings(t_settings *settings)
{
	settings->width = 0;
	settings->height = 0;
	settings->sky_color = 0;
	settings->ground_color = 0;
}

int		main(int ac, char **av)
{
	char		*path;
	int			fd;
	t_settings	settings;

	init_settings(&settings);
	if (ac < 2)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
	}
	path = av[1];
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error("Please provide a valid file path.");
		return (FALSE);
	}
	if (parse_config(fd, &settings) == SUCCESS)
		printf("%d | %d\n", settings.sky_color, settings.ground_color);
	close(fd);
	return (TRUE);
}