/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ull_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 10:05:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/12 11:22:27 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		*ft_rev_tab(char *tab, int size)
{
	int	i;
	int	swap;

	i = 0;
	while (i < size / 2)
	{
		swap = tab[i];
		tab[i] = tab[size - (i + 1)];
		tab[size - (i + 1)] = swap;
		i++;
	}
	return (tab);
}

char			*ft_ull_base(unsigned long long nbr, char *base)
{
	int		i;
	int		baselen;
	char	*ret;

	i = 0;
	baselen = ft_strlen(base);
	if (nbr == 0)
		return (ft_strdup("0"));
	if (!(ret = malloc(sizeof(char) * (ft_uintlen(nbr, baselen) + 1))))
		return (NULL);
	while (nbr)
	{
		ret[i] = base[nbr % baselen];
		nbr /= baselen;
		i++;
	}
	ret[i] = '\0';
	return (ft_rev_tab(ret, ft_strlen(ret)));
}
