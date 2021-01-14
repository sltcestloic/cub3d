/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:25:51 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/14 11:34:08 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error(char *message)
{
	printf("Error\n");
	printf(HRED);
	printf("%s\n", message);
	printf(RESET);
	return (ERROR);
}
