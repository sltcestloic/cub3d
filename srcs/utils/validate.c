/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:26:39 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/13 13:58:12 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int				is_valid_sprite_char(char c)
{
	return (c == '2' || c == '3' || c == '4' || c == '5' || c == '6');
}

int				is_wall(char c)
{
	return (c == '9' || c == '1');
}

int				is_valid_map_char(char c)
{
	return (c == '0' || is_valid_player_char(c) ||
		is_valid_sprite_char(c) || is_wall(c));
}

int			validate_args(int ac, char **av, int *fd, t_view *view)
{
	if (ac < 2 || ac > 3)
	{
		print_error("Usage: ./cub3d <map path> (--save)");
		return (FALSE);
	}
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save") != 0)
			return (print_error("Usage: ./cub3d <map path> (--save)") + 1);
		view->save = TRUE;
	}
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
	{
		print_error("Please provide a valid file path.");
		return (FALSE);
	}
	return (TRUE);
}
