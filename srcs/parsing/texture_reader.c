/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 13:52:19 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/16 13:28:17 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_texture(t_texture texture)
{
	if (texture.img == NULL)
		return (print_error("At least one texture is invalid in .cub file."));
	return (SUCCESS);
}

t_texture	read_texture(char *path, t_view *view)
{
	t_texture	texture;
	int			fd;

	fd = open(path, O_RDONLY);
	close(fd);
	if (fd == -1)
		print_error_exit("Invalid texture path in .cub file.", 1);
	texture.img = mlx_xpm_file_to_image(view->mlx, path, &texture.width,
			&texture.height);
	if (texture.img == NULL)
		print_error_exit("Invalid texture file in .cub file.", 1);
	texture.addr = (int *)mlx_get_data_addr(texture.img,
			&texture.bits_per_pixel, &texture.line_len, &texture.endian);
	return (texture);
}
