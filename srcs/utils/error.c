/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:25:51 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/28 10:42:58 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	print_error_exit(char *message, int ext)
{
	printf("Error\n");
	printf(HRED);
	printf("%s\n", message);
	printf(RESET);
	if (ext)
		exit(0);
	return (ERROR);
}

int	print_error(char *message)
{
	return (print_error_exit(message, 0));
}
