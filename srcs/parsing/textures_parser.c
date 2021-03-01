/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:21:01 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/01 13:42:13 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int					validate_texture(t_texture texture)
{
	if (texture.img == NULL)
		return (print_error("At least one texture is invalid in .cub file."));
	return (SUCCESS);
}

t_texture			read_texture(char *path, t_view *view)
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

void				parse_static_textures(t_view *view)
{
	view->settings->sprite_texture[SPRITE_HEALTH] =
		read_texture("./textures/.static/heart32.xpm", view);
	view->settings->sprite_texture[SPRITE_TRAP] =
		read_texture("./textures/.static/trap.xpm", view);
	view->settings->sprite_texture[SPRITE_SHROOM] =
		read_texture("./textures/.static/shroom.xpm", view);
	view->settings->cup_texture[0] =
		read_texture("./textures/.static/cup0.xpm", view);
	view->settings->cup_texture[1] =
		read_texture("./textures/.static/cup1.xpm", view);
	view->settings->cup_texture[2] =
		read_texture("./textures/.static/cup2.xpm", view);
	view->settings->heart_empty_texture =
		read_texture("./textures/.static/heart_empty.xpm", view);
	view->settings->win_screen =
		read_texture("./textures/.static/win.xpm", view);
	view->settings->hud_texture =
		read_texture("./textures/.static/hud.xpm", view);
}

static int			parse_texture2(char **split, t_view *view)
{
	if (ft_strcmp(split[0], "WE") == 0)
	{
		view->settings->west_texture = read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->west_texture));
	}
	else if (ft_strcmp(split[0], "S") == 0)
	{
		view->settings->sprite_texture[SPRITE_DEFAULT] =
			read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->
			sprite_texture[SPRITE_DEFAULT]));
	}
	return (SUCCESS);
}

int					parse_texture(char **split, t_view *view)
{
	if (ft_strcmp(split[0], "NO") == 0)
	{
		view->settings->north_texture = read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->north_texture));
	}
	else if (ft_strcmp(split[0], "SO") == 0)
	{
		view->settings->south_texture = read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->south_texture));
	}
	else if (ft_strcmp(split[0], "EA") == 0)
	{
		view->settings->east_texture = read_texture(split[1], view);
		free_split(split);
		return (validate_texture(view->settings->east_texture));
	}
	return (parse_texture2(split, view));
}
