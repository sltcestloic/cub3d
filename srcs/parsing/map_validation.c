/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:26:16 by lbertran          #+#    #+#             */
/*   Updated: 2021/02/08 16:01:31 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	run_map_validation(t_map *map, int x, int y)
{
	if (map->content_copy[y][x] != '1')
	{
		if (x == 0 || y == 0 || x == map->longest - 1 || y == map->lines - 1)
			print_error_exit("Invalid map. (Check #1)", 1);
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
	if (player->posx == -1)
	{
		player->posx = x;
		player->posy = y;
		set_direction(player, direction);
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
		else if (line[i] == '2')
			parse_sprite(i, view->map->lines, view);
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
	map->content_copy[(int)player->posy][(int)player->posx] = '0';
	run_map_validation(map, (int)player->posx, (int)player->posy);
	return (TRUE);
}
