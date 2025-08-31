/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:00:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/31 14:13:54 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_doors(t_game *game)
{
	int	x;
	int	y;
	int	door_count;

	door_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'D')
				door_count++;
			x++;
		}
		y++;
	}
	return (door_count);
}

void	valid_door(t_game *game, int y, int x)
{
	int	left;
	int	right;
	int	up;
	int	down;

	left = game->map.grid[y][x - 1];
	right = game->map.grid[y][x + 1];
	up = game->map.grid[y - 1][x];
	down = game->map.grid[y + 1][x];
	if (left == '1' && right == '1' && up == '0' && down == '0')
		return ;
	if (up == '1' && down == '1' && left == '0' && right == '0')
		return ;
	error_and_cleanup("Error: invalid door placement", game);
}

void	init_doors(t_game *game)
{
	int (x), (y), (door_index);
	game->map.door_count = count_doors(game);
	if (game->map.door_count == 0)
	{
		game->map.doors = NULL;
		return ;
	}
	game->map.doors = malloc(sizeof(t_door) * game->map.door_count);
	if (!game->map.doors)
		error_and_cleanup("Failed to allocate doors", game);
	door_index = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			if (game->map.grid[y][x] == 'D')
				valid_door(game, y, x);
			x++;
		}
		y++;
	}
}

t_door	*get_door_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map.door_count)
	{
		if (game->map.doors[i].x == x && game->map.doors[i].y == y)
			return (&game->map.doors[i]);
		i++;
	}
	return (NULL);
}
