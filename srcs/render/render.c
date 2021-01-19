/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:27:54 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/19 13:50:43 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define WIDTH 2
#include <time.h>

int		randomrgb()
{
        time_t  t;

        srand(time(&t));
        return (rgbint(rand() % 255, rand() % 255, rand() % 255));
}

void    draw_point(int x, int y, int rgb, t_view *view)
{
    int     i;

    i = 0;
    for(int ny=-WIDTH; ny<=WIDTH; ny++)
		for(int nx=-WIDTH; nx<=WIDTH; nx++)
            if(nx*nx+ny*ny <= WIDTH*WIDTH)
                mlx_pixel_put(view->mlx, view->window, nx + x, ny + y, rgb);
}

int		render_frame(t_view *view)
{
	draw_point(view->circle->x, view->circle->y, randomrgb(), view);
	handle_keyboard(view);
	return (0);
}