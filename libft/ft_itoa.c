/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:21:02 by lbertran          #+#    #+#             */
/*   Updated: 2020/12/22 16:06:53 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*ret;
	int		neg;
	int		len;
	long	nb;

	nb = nbr;
	neg = nb < 0;
	len = ft_intlen(nb);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(ret, len + 1);
	if (neg)
	{
		ret[0] = '-';
		nb = -nb;
	}
	while (len-- > neg)
	{
		ret[len] = nb % 10 + 48;
		nb /= 10;
	}
	return (ret);
}
