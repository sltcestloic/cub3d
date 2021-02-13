/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:47:20 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/13 13:55:52 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	decrease_effects(t_view *view)
{
	if (view->blackout > 0)
		view->blackout--;
	if (view->lsd > 0)
		view->lsd--;
}

int		get_ground_color(t_view *view)
{
	int	color;
	int	i;
	int	j;

	j = view->lsd;
	color = view->settings->ground_color;
	i = view->blackout;
	if (j && !i)
		color *= 0.9 * j;
	while (i)
	{
		color = (color >> 1) & 8355711;
		i--;
	}
	return (color);
}

int		get_sky_color(t_view *view)
{
	int	color;
	int	i;
	int	j;

	j = view->lsd;
	color = view->settings->sky_color;
	i = view->blackout;
	if (j && !i)
		color *= 0.9 * j;
	while (i)
	{
		color = (color >> 1) & 8355711;
		i--;
	}
	return (color);
}

int		get_texture_color(t_view *view, t_texture texture, int tx, int ty)
{
	int	color;
	int	i;
	int	j;

	j = view->lsd;
	color = texture.addr[(ty * texture.width) + tx];
	i = view->blackout;
	if (j && !i)
		color *= 0.9 * j;
	while (i)
	{
		color = (color >> 1) & 8355711;
		i--;
	}
	return (color);
}
