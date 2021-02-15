/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:56:57 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/15 13:00:54 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_settings2(t_settings *settings)
{
	if (settings->cup_texture[0].img == NULL)
		return (print_error("Cup texture 0 not specified in .cub file"));
	if (settings->cup_texture[1].img == NULL)
		return (print_error("Cup texture 0 not specified in .cub file"));
	if (settings->cup_texture[2].img == NULL)
		return (print_error("Cup texture 0 not specified in .cub file"));
	if (settings->heart_empty_texture.img == NULL)
		return (print_error("Empty heart texture not specified in .cub file"));
	if (settings->hud_texture.img == NULL)
		return (print_error("HUD texture not specified in .cub file"));
	if (settings->sprite_texture[SPRITE_HEALTH].img == NULL)
		return (print_error("Health texture not specified in .cub file"));
	if (settings->sprite_texture[SPRITE_SHROOM].img == NULL)
		return (print_error("Shroom texture not specified in .cub file"));
	if (settings->sprite_texture[SPRITE_TRAP].img == NULL)
		return (print_error("Trap texture not specified in .cub file"));
	if (settings->win_screen.img == NULL)
		return (print_error("Win screen texture not specified in .cub file"));
	return (SUCCESS);
}

int	validate_settings(t_settings *settings, t_player *player)
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
		return(print_error("No player in map."));
	return (validate_settings2(settings));
}