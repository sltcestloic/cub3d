/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:26:39 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/28 14:10:37 by lbertran         ###   ########lyon.fr   */
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

int				is_valid_texture_entry(char *entry)
{
	return (ft_strcmp(entry, "NO") == 0 || ft_strcmp(entry, "SO") == 0
		|| ft_strcmp(entry, "EA") == 0 || ft_strcmp(entry, "WE") == 0
		|| ft_strcmp(entry, "S") == 0);
}
