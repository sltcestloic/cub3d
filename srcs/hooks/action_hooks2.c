/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:54:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/23 13:55:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		handle_key_press2(int keycode, t_view *view)
{
	if (keycode == 49)
		player_jump(view);
	else if (keycode == 48)
		toggle_mouse(view);
	return (0);
}
