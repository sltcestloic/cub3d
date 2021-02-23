/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:13:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/23 13:55:29 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# define NORTH	0
# define SOUTH	1
# define EAST 	2
# define WEST	3
# define SPRITE_DEFAULT 0
# define SPRITE_HEALTH 1
# define SPRITE_TRAP 2
# define SPRITE_SHROOM 3
# define SPRITE_CUP 4
# define MAX_HEALTH 5
# define BYTES_PER_PIXEL 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

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
	t_texture		win_screen;
	t_texture		hud_texture;
	t_texture		heart_empty_texture;
	t_texture		sprite_texture[4];
	t_texture		cup_texture[3];
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
	int				visible;
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
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			vel_y;
	double			ground_y;
	double			spawn_px;
	double			spawn_py;
	double			spawn_dx;
	double			spawn_dy;
	double			spawn_plx;
	double			spawn_ply;
	int				health;
	int				move_count;
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
	int				type;
	int				visible;
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
	double			move_speed;
	double			*z_buffer;
	t_sprite		*sprites;
	int				sprite_count;
	int				save;
	long long		start_timestamp;
	long long		frame_timestamp;
	int				blackout;
	int				lsd;
	int				finished;
	int				animation;
}					t_view;

/*
** Parsing
*/

int					parse_config(int fd, t_map *map, t_view *view);
int					parse_resolution(char *line, t_settings *settings);
int					parse_color(char *line, t_settings *settings, int ground);
int					parse_texture(char **split, t_view *view);
int					parse_texture4(char **split, t_view *view);
int					parse_map_line(char *line, t_view *view);
void				parse_sprite(int x, int y, t_view *view, int type);
t_texture			read_texture(char *path, t_view *view);
void				copy_content(char **old, char **next, int mlc);

/*
** Window
*/

void				init_window(t_settings settings, t_view view);
int					create_bitmap(t_view *view);

/*
** Print
*/

int					print_error(char *message);
int					print_error_exit(char *message, int ext);

/*
** Pixels / colors
*/

int					rgbint(int r, int g, int b);
int					rgbint_r(int rgb);
int					rgbint_g(int rgb);
int					rgbint_b(int rgb);
void				put_pixel(t_view *view, int x, int y, int color);
int					get_pixel_color(t_image *image, int x, int y);
void				fill_window(t_view *view, int color);

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
int					validate_texture(t_texture texture);
int					is_valid_map_char(char c);
int					is_valid_player_char(char c);
int					is_valid_sprite_char(char c);
int					is_wall(char c);
int					is_valid_texture_entry(char *entry);
int					validate_settings(t_settings *settings, t_player *player);

/*
** Hooks
*/

int					handle_close_button(void);
int					handle_key_press(int keycode, t_view *view);
int					handle_key_press2(int keycode, t_view *view);
int					handle_key_release(int keycode, t_view *view);
int					handle_click_release(int button, int x, int y, t_view *view);
int					handle_click(int button, int x, int y, t_view *view);
int					handle_mouse_motion(int x, int y, t_view *view);
void				handle_keyboard(t_view *view);

/*
** Sprites
*/

void				sort_sprites(t_view *view);
void				calculate_distances(t_view *view);
void				reset_sprites(t_view *view);

/*
** Render
*/

int					render_frame(t_view *view);
void				do_raycast(t_view *view);
void				do_spritecast(t_view *view);
void				draw_ray(t_view *view, t_ray *ray, int x);
void				draw_sprite(t_view *view, t_sprite *sprite);
void				draw_hud(t_view *view);
void				draw_health(t_view *view);
void				draw_fps(t_view *view);
void				draw_win_screen(t_view *view, int minutes, int seconds);
void				save_screen(t_view *view);

/*
** Player/camera movement
*/

void				rotate_camera_lr(t_view *view, int right, int mouse);
void				rotate_camera_ud(t_view *view, int up, int mouse);
void				move_player_fb(t_view *view, int forward);
void				move_player_lr(t_view *view, int forward);
int					collision(t_view *view, double x, double y);

/*
** Time
*/

long long			current_millis(void);

/*
** Colors
*/

int					get_ground_color(t_view *view);
int					get_sky_color(t_view *view);
int					get_texture_color(t_view *view, t_texture texture, int tx, int ty);
int					get_sprite_color(t_view *view, t_sprite *sprite, int tx, int ty);
void				decrease_effects(t_view *view);

/*
** Jump
*/

void				update_horizon(t_view *view);
void				player_jump(t_view *view);

/*
** Mouse
*/

void				hide_mouse(t_view *view);
void				show_mouse(t_view *view);
void				toggle_mouse(t_view *view);

#endif
