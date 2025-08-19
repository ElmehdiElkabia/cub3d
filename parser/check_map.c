/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:09:07 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:33:30 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == ' ' || *line == 'N'
			|| *line == 'S' || *line == 'E' || *line == 'W')
			return (1);
		line++;
	}
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n');
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
				print_error("Invalid character in map");
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
		print_error("No player found in map");
	if (player_count > 1)
		print_error("Multiple player positions in map");
}

void	check_closure(t_game *game)
{
	char	**copy;
	int		x;
	int		y;

	x = 0;
	y = 0;
	copy = duplicate_map(game->map.grid);
	if (!copy)
	{
		print_error("Failed to duplicate map copy");
	}
	find_player_position(game->map.grid, &x, &y);
	copy[y][x] = '0';
	flood_fill(copy, x, y);
	ft_free_split(copy);
}
