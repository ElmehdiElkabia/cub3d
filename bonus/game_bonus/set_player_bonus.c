/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:48:11 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	set_position(t_player *player, double y, double x)
{
	player->pos.y = y + 0.5;
	player->pos.x = x + 0.5;
}

void	set_dir(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	set_plane(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	set_player(t_player *player, double y, double x, int id)
{
	if (id == 0)
	{
		set_position(player, y, x);
		set_dir(&player->dir, 0, -1);
		set_plane(&player->plane, 0.66, 0);
	}
	else if (id == 1)
	{
		set_position(player, y, x);
		set_dir(&player->dir, 0, 1);
		set_plane(&player->plane, -0.66, 0);
	}
	else if (id == 2)
	{
		set_position(player, y, x);
		set_dir(&player->dir, 1, 0);
		set_plane(&player->plane, 0, 0.66);
	}
	else if (id == 3)
	{
		set_position(player, y, x);
		set_dir(&player->dir, -1, 0);
		set_plane(&player->plane, 0, -0.66);
	}
}

void	set_player_direction(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = game->map.grid;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N')
				set_player(&game->player, y, x, 0);
			else if (map[y][x] == 'S')
				set_player(&game->player, y, x, 1);
			else if (map[y][x] == 'E')
				set_player(&game->player, y, x, 2);
			else if (map[y][x] == 'W')
				set_player(&game->player, y, x, 3);
			x++;
		}
		y++;
	}
}
