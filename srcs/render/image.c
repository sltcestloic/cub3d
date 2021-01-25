/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:05:12 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/21 13:10:28 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** https://harm-smits.github.io/42docs/libs/
** minilibx/getting_started.html#writing-pixels-to-a-image
*/

void	put_pixel_to_img(t_image *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}
