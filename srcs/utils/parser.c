/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:36:35 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 16:41:03 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		parse_line(char *line, t_settings *settings)
{
	if (line[0] == 'R')
		return (parse_resolution(line, settings));
	return (ERROR);
}

int		parse_config(int fd, t_settings *settings)
{
	char	*line;

	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_isalpha(line[0]))
			return (parse_line(line, settings));
	}
	return (SUCCESS);
}