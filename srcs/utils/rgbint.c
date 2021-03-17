/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:46:43 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/17 13:08:47 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgbint(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (65536 * r + 256 * g + b);
}

int	rgbint_chr(char *r, char *g, char *b)
{
	char	*rtr;
	char	*gtr;
	char	*btr;
	int		ret;

	rtr = ft_strtrim(r, " ");
	gtr = ft_strtrim(g, " ");
	btr = ft_strtrim(b, " ");
	if (ft_atoi(rtr) < 0 || ft_atoi(rtr) > 255 || ft_atoi(gtr) < 0
		|| ft_atoi(gtr) > 255 || ft_atoi(btr) < 0 || ft_atoi(btr) > 255)
		return (-1);
	ret = (65536 * ft_atoi(rtr) + 256 * ft_atoi(gtr) + ft_atoi(btr));
	free(rtr);
	free(gtr);
	free(btr);
	return (ret);
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
