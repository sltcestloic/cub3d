/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:57:17 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/19 11:06:29 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_jump(t_view *view)
{
	if (view->player->vel_y != 0)
		return ;
	view->player->vel_y = 20;
	view->player->ground_y = view->horizon;
}

void	update_horizon(t_view *view)
{
	if (view->player->vel_y == 0)
		return ;
	view->horizon += view->player->vel_y;
	if (view->horizon - 0.5 < view->player->ground_y)
	{
		view->player->vel_y = 0;
		view->horizon = view->player->ground_y;
	}
	else
		view->player->vel_y -= 1.55;
}