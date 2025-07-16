/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:09:07 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/16 18:52:20 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == ' ' ||
			*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			return (1);
		line++;
	}
	return (0);
}

int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || 
			c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
			c == ' ' || c == '\n' );
}

void	check_characters(t_game *game)
{
	int	y;
	int	x;
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
	int	y;
	int	x;
	int	player_count;
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


char	**duplicate_map(char **original)
{
	int		i;
	int		j;
	char	**copy;

	i = ft_strlen(*original);
	j = 0;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		print_error("Failed to allocate map copy");
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		while (copy[i][j])
		{
			if (copy[i][j] == 'N' || copy[i][j] == 'S' ||
				copy[i][j] == 'E' || copy[i][j] == 'W')
				copy[i][j] = '0';
			j++;
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	find_player_position(char **map, int *px, int *py)
{
	int	y = 0;
	int	x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' ||
				map[y][x] == 'E' || map[y][x] == 'W')
			{
				*px = x;
				*py = y;
				return;
			}
			x++;
		}
		y++;
	}
	print_error("Player not found when trying to locate spawn point");
}

void flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		print_error("Map is not closed");

	if (map[y][x] == ' ' || map[y][x] == '\0')
		print_error("Map is not closed");

	if (map[y][x] != '0' && map[y][x] != '1')
		return;

	if (map[y][x] == '1')
		return;

	map[y][x] = 'F';

	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}


void check_closure(t_game *game)
{
	char	**copy;
	int		x, y;

	x = 0;
	y = 0;
	copy = duplicate_map(game->map.grid); 
	find_player_position(game->map.grid, &x, &y);
	copy[y][x] = '0';
	flood_fill(copy, x, y);
	ft_free_split(copy);
}