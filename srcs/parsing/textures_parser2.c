/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 12:56:43 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/13 13:00:32 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_texture4(char **split, t_view *view)
{
	if (ft_strcmp(split[0], "GG") == 0)
	{
		view->settings->win_screen =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->sprite_texture[SPRITE_TRAP]));
	}
	return (SUCCESS);
}
