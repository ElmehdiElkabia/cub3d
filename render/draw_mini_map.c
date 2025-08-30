/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:44:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 10:46:07 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_square_minimap(t_game *game, int tile_y, int tile_x, int color)
{
	int	start_x;
	int	start_y;
	int	py;
	int	px;

	start_x = tile_x * MINI_TILE;
	start_y = tile_y * MINI_TILE;
	py = 0;
	while (py < MINI_TILE)
	{
		px = 0;
		while (px < MINI_TILE)
		{
			my_mlx_pixel_put(&game->img, start_x + px, start_y + py, color);
			px++;
		}
		py++;
	}
}

void	draw_player_minimap(t_game *game)
{
	int		size;
	double	center_tile_x;
	double	center_tile_y;
	int		px;
	int		py;
	int		dy;
	int		dx;

	size = 4;
	center_tile_x = MINI_VIEW_W / 2;
	center_tile_y = MINI_VIEW_H / 2;
	px = (center_tile_x * MINI_TILE) + (game->player.pos.x
			- (int)game->player.pos.x) * MINI_TILE;
	py = (center_tile_y * MINI_TILE) + (game->player.pos.y
			- (int)game->player.pos.y) * MINI_TILE;
	dy = -size / 2;
	while (dy < size / 2)
	{
		dx = -size / 2;
		while (dx < size / 2)
		{
			my_mlx_pixel_put(&game->img, px + dx, py + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	start_x;
	int	start_y;
	int	y;
	int	x;
	int	map_x;
	int	map_y;

	start_x = (int)game->player.pos.x - MINI_VIEW_W / 2;
	start_y = (int)game->player.pos.y - MINI_VIEW_H / 2;
	y = 0;
	while (y < MINI_VIEW_H)
	{
		x = 0;
		while (x < MINI_VIEW_W)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			if (map_x < 0 || map_x >= game->map.width - 1 || map_y < 0
				|| map_y >= game->map.height)
			{
				draw_square_minimap(game, y, x, 0x000000);
				x++;
				continue ;
			}
			if (game->map.grid[map_y][map_x] == '1')
				draw_square_minimap(game, y, x, 0x333333);
			else if (game->map.grid[map_y][map_x] == 'D')
				draw_square_minimap(game, y, x, 0xF04000);
			else if (game->map.grid[map_y][map_x] == 'O')
				draw_square_minimap(game, y, x, 0x799C00);
			else
				draw_square_minimap(game, y, x, 0xCCCCCC);
			x++;
		}
		y++;
	}
	draw_player_minimap(game);
}
