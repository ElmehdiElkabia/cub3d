/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:46:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/24 12:28:59 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	update_position(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player.pos.x);
	map_y = (int)(game->player.pos.y);
	if (game->map.grid[map_y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map.grid[(int)new_y][map_x] != '1')
		game->player.pos.y = new_y;
}

int	game_loop(t_game *game)
{
	double	new_x;
	double	new_y;

	handle_exit(game);
	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	handle_movement(&new_x, &new_y, game);
	handle_rotation(game);
	update_position(game, new_x, new_y);
	render_frame(game);
	return (0);
}
