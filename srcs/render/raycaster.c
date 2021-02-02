/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:19:24 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/02 12:50:22 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	do_raycast(t_view *view)
{
	int		x;
	t_ray	ray;
	t_image	img;

	(void)ray;
	x = 0;
	img.img = mlx_new_image(view->mlx, view->settings->width,
		view->settings->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_len, &img.endian);
	while (x < view->settings->width)
	{	
		x++;
	}
	mlx_put_image_to_window(view->mlx, view->window, img.img, 0, 0);
}
