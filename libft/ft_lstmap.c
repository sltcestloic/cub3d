/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:05:46 by lbertran          #+#    #+#             */
/*   Updated: 2020/12/21 16:56:26 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *list, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*new_list;

	if (!list)
		return (NULL);
	if (!(new_list = ft_lstnew((*f)(list->content))))
	{
		ft_lstclear(&list, del);
		return (NULL);
	}
	list = list->next;
	while (list)
	{
		if (!(new_elem = ft_lstnew((*f)(list->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		list = list->next;
	}
	return (new_list);
}
