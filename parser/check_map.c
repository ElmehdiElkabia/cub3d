/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:09:07 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 12:20:24 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n' || c == 'D');
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == 'D')
		{
			while (line[i])
			{
				if (!is_valid_map_char(line[i]))
					return (0);
				i++;
			}
			return (1);
		}
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (0);
}

void	check_characters(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c))
				error_and_cleanup("Invalid character in map", game);
			x++;
		}
		y++;
	}
}

void	check_player(t_game *game)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 0)
		error_and_cleanup("No player found in map", game);
	if (player_count > 1)
		error_and_cleanup("Multiple player positions in map", game);
}

static int	is_edge(int x, int y, int actual_len, int max_y)
{
	return (y == 0 || y == max_y - 1 || x == 0 || x == actual_len - 1);
}

static int	is_space_or_outside(char *line, int x)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (x >= len || line[x] == ' ');
}

int	is_boundary_violation(char **map, int x, int y)
{
	int	actual_len;
	int	north_len;
	int	south_len;
	int	max_y;

	max_y = 0;
	while (map[max_y])
		max_y++;
	actual_len = ft_strlen(map[y]);
	if (actual_len > 0 && map[y][actual_len - 1] == '\n')
		actual_len--;
	if (is_edge(x, y, actual_len, max_y))
		return (1);
	if (y > 0 && is_space_or_outside(map[y - 1], x))
		return (1);
	if (y < max_y - 1 && is_space_or_outside(map[y + 1], x))
		return (1);
	if (x > 0 && map[y][x - 1] == ' ')
		return (1);
	if (x < actual_len - 1 && map[y][x + 1] == ' ')
		return (1);
	return (0);
}

void	check_all_zeros_enclosed(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == 'N'
				|| game->map.grid[y][x] == 'S' || game->map.grid[y][x] == 'E'
				|| game->map.grid[y][x] == 'W' || game->map.grid[y][x] == 'D')
			{
				if (is_boundary_violation(game->map.grid, x, y))
					error_and_cleanup("Map is not closed", game);
			}
			x++;
		}
		y++;
	}
}

void	check_closure(t_game *game)
{
	char	**copy;
	int		x;
	int		y;
	int		error_flag;

	check_all_zeros_enclosed(game);
	x = 0;
	y = 0;
	copy = duplicate_map(game->map.grid);
	if (!copy)
		error_and_cleanup("Failed to duplicate map copy", game);
	find_player_position(game->map.grid, &x, &y);
	copy[y][x] = '0';
	error_flag = 0;
	flood_fill_recursive(copy, x, y, &error_flag);
	ft_free_split(copy);
	if (error_flag)
		error_and_cleanup("Map is not closed", game);
}
