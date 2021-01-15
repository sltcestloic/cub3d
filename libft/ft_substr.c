/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:15:45 by lbertran          #+#    #+#             */
/*   Updated: 2020/12/01 16:05:13 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]) + 1;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (start >= slen)
	{
		ft_bzero(ret, len + 1);
		return (ret);
	}
	while (i < len && s[start])
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}
