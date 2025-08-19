/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:44:44 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:02:31 by eelkabia         ###   ########.fr       */
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

static void	render_screen(t_game *game)
{
	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	render_frame(game);
}

int	update_player(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;

	handle_exit(keycode, game);
	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	update_new_pos(keycode, &new_x, &new_y, game);
	update_position(game, new_x, new_y);
	render_screen(game);
	return (0);
}
