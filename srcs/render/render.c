/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:27:54 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/03 15:25:41 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		render_frame(t_view *view)
{
	t_image	img;

	img.img = mlx_new_image(view->mlx, view->settings->width,
		view->settings->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_len, &img.endian);
	view->image = &img;
	handle_keyboard(view);
	do_raycast(view);
	mlx_put_image_to_window(view->mlx, view->window, img.img, 0, 0);
	return (0);
}

void	draw_ray(t_view *view, t_ray *ray, int x)
{
	int color = rgbint(0, 255, 0);
	int	y;

	y = 0;
	if (ray->side == 0)
		color /= 2;
	while (y < ray->draw_start)
		put_pixel(view->image, x, y++, view->settings->sky_color);
	while (y < ray->draw_end)
		put_pixel(view->image, x, y++, color);
	while (y < view->settings->height)
		put_pixel(view->image, x, y++, view->settings->ground_color);
}
