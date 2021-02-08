/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/08 16:52:10 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include <math.h>
# define NORTH	0
# define SOUTH	1
# define EAST 	2
# define WEST	3

typedef struct		s_texture
{
	void			*img;
	int				width;
	int				height;
	int				*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
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
	char			**content_copy;
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
	int				la_pressed;
	int				ra_pressed;
	int				ua_pressed;
	int				da_pressed;
	int				shift_pressed;
	int				ctrl_pressed;
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
	double			cam_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct		s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_image;

typedef struct		s_sprite
{
	double			pos_x;
	double			pos_y;
	double			invdet;
	double			tr_x;
	double			tr_y;
	int				screen_x;
	int				height;
	int				width;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				order;
	double			distance;
}					t_sprite;

typedef struct		s_view
{
	void			*mlx;
	void			*window;
	t_mouse			*mouse;
	t_settings		*settings;
	t_keyboard		*keyboard;
	t_player		*player;
	t_map			*map;
	t_image			*image;
	int				horizon;
	double			sensivity;
	double			move_speed;
	double			*z_buffer;
	t_sprite		sprites[50];
	int				sprite_count;
}					t_view;


/*
** Parsing
*/

int					parse_config(int fd, t_map *map, t_view *view);
int					parse_resolution(char *line, t_settings *settings);
int					parse_color(char *line, t_settings *settings, int ground);
int					parse_texture(char **split, t_view *view);
int					parse_map_line(char *line, t_view *view);
void				parse_sprite(int x, int y, t_view *view);
void				copy_content(char **old, char **next, int mlc);

/*
** Window
*/

void				init_window(t_settings settings, t_view view);

/*
** Print
*/

int					print_error(char *message);
int					print_error_exit(char *message, int ext);

/*
** Pixels / colors
*/

int					rgbint(int r, int g, int b);
void				put_pixel(t_view *view, int x, int y, int color);
int					get_pixel_color(t_image *image, int x, int y);

/*
** Direction
*/

void				set_direction(t_player *player, char dir);
t_texture			get_texture(int direction, t_view *view);

/*
** Validation
*/

int					validate_map(t_map *map, t_player *player);
int					validate_map_line(char *line, t_view *view);
int					is_valid_map_char(char c);
int					is_valid_player_char(char c);

/*
** Hooks
*/

int					handle_close_button();
int					handle_key_press(int keycode, t_view *view);
int					handle_key_release(int keycode, t_view *view);
int					handle_click_release(int button, int x, int y, t_view *view);
int					handle_click(int button, int x, int y, t_view *view);
int 				handle_mouse_motion(int x, int y, t_view *view);
void				handle_keyboard(t_view *view);

/*
** Render
*/

void				put_pixel_to_img(t_image *img, int x, int y, int color);
int					render_frame(t_view *view);
void				do_raycast(t_view *view);
void				do_spritecast(t_view *view);
void				draw_ray(t_view *view, t_ray *ray, int x);

/*
** Player/camera movement
*/

void				rotate_camera_lr(t_view *view, int right, int mouse);
void				rotate_camera_ud(t_view *view, int up, int mouse);
void				move_player_fb(t_view *view, int forward);
void				move_player_lr(t_view *view, int forward);

#endif
