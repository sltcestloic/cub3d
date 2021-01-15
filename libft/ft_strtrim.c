/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:38:55 by lbertran          #+#    #+#             */
/*   Updated: 2020/11/26 15:40:06 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	while (s1[i] && is_charset(s1[i], set))
		i++;
	while (j && is_charset(s1[j], set))
		j--;
	if (!(ret = malloc(sizeof(char) * (i <= j ? j - i + 2 : 1))))
		return (NULL);
	while (i < j + 1)
	{
		ret[k] = s1[i];
		k++;
		i++;
	}
	ret[k] = '\0';
	return (ret);
}
