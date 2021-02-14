/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:56:43 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/14 13:46:25 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_texture5(char **split, t_view *view)
{
	if (ft_strcmp(split[0], "HUD") == 0)
	{
		view->settings->hud_texture =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->hud_texture));
	}
	if (ft_strcmp(split[0], "HEART_EMPTY") == 0)
	{
		view->settings->heart_empty_texture =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->heart_empty_texture));
	}
	return (SUCCESS);
}

int	parse_texture4(char **split, t_view *view)
{
	if (ft_strcmp(split[0], "GG") == 0)
	{
		view->settings->win_screen =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->win_screen));
	}
	else if (ft_strcmp(split[0], "W1") == 0)
	{
		view->settings->cup_texture[1] =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->cup_texture[1]));
	}
	else if (ft_strcmp(split[0], "W2") == 0)
	{
		view->settings->cup_texture[2] =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->cup_texture[2]));
	}
	else
		return (parse_texture5(split, view));
	return (SUCCESS);
}
