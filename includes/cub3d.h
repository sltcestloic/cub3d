/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/13 16:47:25 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct		s_settings
{
	int				width;
	int				height;
	char			*north_texture;	//SO
	char			*south_texture;	//NO
	char			*east_texture;	//EA
	char			*west_texture;	//WE
	char			*sprite_texture;//S
	int				ground_color;	//F
	int				sky_color;		//C
}					t_settings;

int					parse_config(int fd, t_settings *settings);
void				print_error(char *message);
int					parse_resolution(char *line, t_settings *settings);
int					parse_color(char *line, t_settings *settings, int ground);
int					rgbint(int r, int g, int b);

#endif