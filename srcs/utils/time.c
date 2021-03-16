/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:28:57 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/16 13:47:05 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

long long	current_millis(void)
{
	struct timeval	time;
	long long		s1;
	long long		s2;

	gettimeofday(&time, NULL);
	s1 = (long long)(time.tv_sec) *1000;
	s2 = (time.tv_usec / 1000);
	return (s1 + s2);
}
