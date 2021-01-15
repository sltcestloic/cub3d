/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:39:14 by lbertran          #+#    #+#             */
/*   Updated: 2020/11/24 15:07:55 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void*))
{
	t_list	*swap;

	if (!list)
		return ;
	if (!*list)
		return ;
	if (!del)
		return ;
	while (*list)
	{
		swap = (*list)->next;
		(*del)((*list)->content);
		free(*list);
		*list = swap;
	}
}
