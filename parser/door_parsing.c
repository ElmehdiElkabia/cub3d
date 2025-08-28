/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:00:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/28 00:00:00 by eelkabia         ###   ########.fr       */
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

void	init_doors(t_game *game)
{
	int	x;
	int	y;
	int	door_index;

	game->map.door_count = count_doors(game);
	if (game->map.door_count == 0)
	{
		game->map.doors = NULL;
		printf("No doors found in map\n");
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
			{
				game->map.doors[door_index].x = x;
				game->map.doors[door_index].y = y;
				game->map.doors[door_index].state = DOOR_CLOSED;
				game->map.doors[door_index].anim_progress = 0.0;
				game->map.doors[door_index].anim_speed = 0.05;
				door_index++;
			}
			x++;
		}
		y++;
	}
}

void	print_doors_info(t_game *game)
{
	int	i;

	printf("Found %d doors:\n", game->map.door_count);
	i = 0;
	while (i < game->map.door_count)
	{
		printf("Door %d: position (%d, %d), state: %d\n", 
			i, game->map.doors[i].x, game->map.doors[i].y, game->map.doors[i].state);
		i++;
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
