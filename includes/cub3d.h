/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/01/25 10:41:10 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include <math.h>

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
	int				longest;
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

typedef struct		s_player
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
}					t_player;

typedef struct		s_ray
{
	double			camx;
	double			dirx;
	double			diry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
}					t_ray;

typedef struct		s_view
{
	void			*mlx;
	void			*window;
	t_mouse			*mouse;
	t_settings		*settings;
	t_keyboard		*keyboard;
	t_player		*player;
	t_map			*map;
}					t_view;

typedef struct		s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_image;

int					parse_config(int fd, t_map *map, t_view *view);
int					parse_resolution(char *line, t_settings *settings);
int					parse_color(char *line, t_settings *settings, int ground);
int					parse_texture(char **split, t_view *view);
int					parse_map_line(char *line, t_map *map, t_player *player);

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
void				put_pixel_to_img(t_image *img, int x, int y, int color);
void				do_raycast(t_view *view);

#endif
