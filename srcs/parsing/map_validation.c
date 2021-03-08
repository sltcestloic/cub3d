/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:26:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/03/08 16:48:25 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	run_map_validation(t_map *map, int x, int y)
{
	if (map->content_copy[y][x] != '1')
	{
		if (x == 0 || y == 0 || x == map->longest - 1 || y == map->lines - 1)
		{
			printf("%d %d = %c\n", x, y, map->content_copy[y][x]);
			print_error_exit("Invalid map. (Check #1)", 1);
		}
		if (map->content_copy[y][x] == ' ')
			print_error_exit("Invalid map. (Check #2)", 1);
		map->content_copy[y][x] = '1';
		run_map_validation(map, x + 1, y);
		run_map_validation(map, x + 1, y + 1);
		run_map_validation(map, x + 1, y - 1);
		run_map_validation(map, x, y + 1);
		run_map_validation(map, x, y - 1);
		run_map_validation(map, x - 1, y);
		run_map_validation(map, x - 1, y + 1);
		run_map_validation(map, x - 1, y - 1);
	}
}

void	check_player(int x, int y, char direction, t_player *player)
{
	if (player->pos_x == -1)
	{
		player->pos_x = x + 0.5;
		player->pos_y = y + 0.5;
		set_direction(player, direction);
		player->spawn_px = player->pos_x;
		player->spawn_py = player->pos_y;
		player->spawn_dx = player->dir_x;
		player->spawn_dy = player->dir_y;
		player->spawn_plx = player->plane_x;
		player->spawn_ply = player->plane_y;
	}
	else
		print_error_exit("More than one player in map.", 1);
}

int		validate_map_line(char *line, t_view *view)
{
	size_t	i;

	i = 0;
	while (ft_iswhitespace(line[i]))
		i++;
	if (!line[i] || line[i] != '1')
		return (FALSE);
	while (is_valid_map_char(line[i]) || line[i] == ' ')
	{
		if (is_valid_player_char(line[i]))
			check_player(i, view->map->lines, line[i], view->player);
		else if (is_valid_sprite_char(line[i]))
			parse_sprite(i, view->map->lines, view, line[i] - 48);
		i++;
	}
	if (line[i - 1] != '1')
		return (FALSE);
	return (TRUE);
}

int		validate_map(t_map *map, t_player *player)
{
	if (!(map->content_copy = malloc(sizeof(char *) * (map->lines + 2))))
		return (print_error_exit("Map copy malloc failed.", 1));
	copy_content(map->content, map->content_copy, map->longest);
	if (player->pos_x < 0)
		print_error_exit("No player in map.", 1);
	map->content_copy[(int)player->pos_y][(int)player->pos_x] = '0';
	run_map_validation(map, (int)player->pos_x, (int)player->pos_y);
	return (TRUE);
}
