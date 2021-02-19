/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpimage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:46:29 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/19 12:38:09 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	data_to_bitmap(t_view *view, int fd)
{
	int i;

	i = view->settings->width * view->settings->height - 1;
	while (i >= 0)
	{
		write(fd, &view->image->addr[i * view->image->bits_per_pixel / 8], 4);
		i--;
	}
	return (SUCCESS);
}

static void	reverse_pixel(t_image *img, int line_cnt, int *e, int f)
{
	char	save;
	int		k;

	k = 3;
	while (k >= 0)
	{
		save = img->addr[*e + (line_cnt * img->line_len)];
		img->addr[*e + (line_cnt * img->line_len)] =
			img->addr[f - k + (line_cnt * img->line_len - 1)];
		img->addr[f - k + (line_cnt * img->line_len - 1)] =
			save;
		k--;
		*e = *e + 1;
	}
}

static int	reverse_content(t_view *view)
{
	int		line_cnt;
	int		e;
	int		f;

	line_cnt = 0;
	while (line_cnt < view->settings->height)
	{
		e = 0;
		f = view->image->line_len;
		while (e < f && e != f)
		{
			reverse_pixel(view->image, line_cnt, &e, f);
			f -= 4;
		}
		line_cnt++;
	}
	return (SUCCESS);
}

static int	bitmap_info_header(t_view *view, int fd)
{
	int		header_info_size;
	int		plane_nbr;
	int		o_count;

	header_info_size = INFO_HEADER_SIZE;
	plane_nbr = 1;
	write(fd, &header_info_size, 4);
	write(fd, &view->settings->width, 4);
	write(fd, &view->settings->height, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &view->image->bits_per_pixel, 2);
	o_count = 0;
	while (o_count < 28)
	{
		write(fd, "\0", 1);
		o_count++;
	}
	return (SUCCESS);
}

int			create_bitmap(t_view *view)
{
	int		fd;
	int		file_size;
	int		first_pix;
	char	*name;

	name = ft_strdup("image.bmp");
	fd = open(name, O_CREAT | O_RDWR, 0777);
	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + 4 +
		(view->settings->width * view->settings->height) * 4;
	first_pix = FILE_HEADER_SIZE + INFO_HEADER_SIZE + 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bitmap_info_header(view, fd);
	reverse_content(view);
	data_to_bitmap(view, fd);
	close(fd);
	free(name);
	exit(0);
	return (SUCCESS);
}
