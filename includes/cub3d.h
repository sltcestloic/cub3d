/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/20 09:56:31 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "../mlx/mlx.h"

typedef struct		s_texture
{
	void			*img;
	int				width;
	int				height;
}					t_texture;

typedef struct		s_settings
{
	int				width;
	int				height;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		east_texture;
	t_texture		west_texture;
	t_texture		sprite_texture;
	int				ground_color;
	int				sky_color;
}					t_settings;

typedef struct		s_map
{
	char			**content;
	int				lines;
	int				px;
	int				py;
}					t_map;

typedef struct		s_mouse
{
	int				pressed;
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_keyboard
{
	int				w_pressed;
	int				a_pressed;
	int				s_pressed;
	int				d_pressed;
}					t_keyboard;

typedef struct		s_circle
{
	int				x;
	int				y;
}					t_circle;

typedef struct		s_view
{
	void			*mlx;
	void			*window;
	t_mouse			*mouse;
	t_settings		*settings;
	t_keyboard		*keyboard;
	t_circle		*circle;
}					t_view;

int					parse_config(int fd, t_map *map, t_view *view);
int					parse_resolution(char *line, t_settings *settings);
int					parse_color(char *line, t_settings *settings, int ground);
int					parse_texture(char **split, t_view *view);
int					parse_map_line(char *line, t_map *map);

int					validate_map(t_map *map);

void				init_window(t_settings settings, t_view view);

int					print_error(char *message);
int					rgbint(int r, int g, int b);

int					is_valid_map_char(char c);
int					is_valid_player_char(char c);

int					handle_close_button();
int					handle_key_press(int keycode, t_view *view);
int					handle_key_release(int keycode, t_view *view);
int					handle_click_release(int button, int x, int y, t_view *view);
int					handle_click(int button, int x, int y, t_view *view);

void				handle_keyboard(t_view *view);

int					render_frame(t_view *view);

#endif
