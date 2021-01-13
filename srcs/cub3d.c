/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:12:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 16:53:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	char		*path;
	int			fd;
	t_settings	settings;

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
		printf("%dx%d\n", settings.width, settings.height);
	close(fd);
	return (TRUE);
}