/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:46:43 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/25 11:18:09 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	rgbint(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (65536 * r + 256 * g + b);
}

int	rgbint_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

int	rgbint_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

int	rgbint_b(int rgb)
{
	return (rgb & 255);
}
