/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:36:05 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/12 09:57:24 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned long long nbr)
{
	char	*ret;
	int		len;
	long	nb;

	nb = nbr;
	len = ft_intlen(nb);
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(ret, len + 1);
	while (len--)
	{
		ret[len] = nb % 10 + 48;
		nb /= 10;
	}
	return (ret);
}
