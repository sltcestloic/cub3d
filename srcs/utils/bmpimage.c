/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpimage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:46:29 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/13 13:56:51 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned char*	create_bmp_file_header(int height, int stride)
{
    int file_size;
    static unsigned char fileHeader[] = {
        0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
    };

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(file_size);
    fileHeader[3] = (unsigned char)(file_size >> 8);
    fileHeader[4] = (unsigned char)(file_size >> 16);
    fileHeader[5] = (unsigned char)(file_size >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
    return fileHeader;
}

unsigned char*	create_bmp_info_header(int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,
        0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
    };

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
    return infoHeader;
}

void		generate_bmp(unsigned char* image, int height, int width, char* imageFileName)
{
	FILE* imageFile;
    unsigned char padding[3] = {0, 0, 0};
    int paddingSize;
    int stride;
	int i;

	i = 0;
	paddingSize = (4 - (width * BYTES_PER_PIXEL) % 4) % 4;
	stride = (width * BYTES_PER_PIXEL) + paddingSize;
    imageFile = fopen(imageFileName, "wb");
    fwrite(create_bmp_file_header(height, stride), 1, FILE_HEADER_SIZE, imageFile);
    fwrite(create_bmp_info_header(height, width), 1, INFO_HEADER_SIZE, imageFile);
    while (i < height)
	{
        fwrite(image + (i * width * BYTES_PER_PIXEL), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
		i++;
    }
    fclose(imageFile);
}

void		save_screen(t_view *view)
{
	unsigned char	image[view->settings->height][view->settings->width][3];
	char			*file_name;
	int				x;
	int				y;

	file_name = "image.bmp";
	x = 0;
	y = 0;
	while (x < view->settings->width)
	{
		while (y < view->settings->height)
		{
			image[y][x][2] = rgbint_r(get_pixel_color(view->image, x, y));
			image[y][x][1] = rgbint_g(get_pixel_color(view->image, x, y));
			image[y][x][0] = rgbint_b(get_pixel_color(view->image, x, y));
			y++;
		}
		x++;
	}
	generate_bmp((unsigned char*) image, view->settings->height, view->settings->width, file_name);
	exit(0);
}