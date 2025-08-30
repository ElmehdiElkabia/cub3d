/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:00:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 12:15:11 by eelkabia         ###   ########.fr       */
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

static void	set_door_props(t_door *door, int x, int y)
{
	door->x = x;
	door->y = y;
	door->state = DOOR_CLOSED;
	door->anim_progress = 0.0;
	door->anim_speed = 0.05;
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
				set_door_props(&game->map.doors[door_index++], x, y);
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
