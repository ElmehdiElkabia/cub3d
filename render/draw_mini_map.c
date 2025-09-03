/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:44:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/03 09:42:05 by ayadouay         ###   ########.fr       */
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
	t_mini	data;

	data.size = 4;
	data.center_tile_x = MINI_VIEW_W / 2;
	data.center_tile_y = MINI_VIEW_H / 2;
	data.px = (data.center_tile_x * MINI_TILE) + (game->player.pos.x
			- (int)game->player.pos.x) * MINI_TILE;
	data.py = (data.center_tile_y * MINI_TILE) + (game->player.pos.y
			- (int)game->player.pos.y) * MINI_TILE;
	data.dy = -data.size / 2;
	while (data.dy < data.size / 2)
	{
		data.dx = -data.size / 2;
		while (data.dx < data.size / 2)
		{
			my_mlx_pixel_put(&game->img, data.px + data.dx, data.py + data.dy,
				0xFF0000);
			data.dx++;
		}
		data.dy++;
	}
}

void	check_case_draw(t_game *game, t_mini *data)
{
	if (game->map.grid[data->map_y][data->map_x] == '1')
		draw_square_minimap(game, data->y, data->x, 0x333333);
	else if (game->map.grid[data->map_y][data->map_x] == 'D')
		draw_square_minimap(game, data->y, data->x, 0xF04000);
	else if (game->map.grid[data->map_y][data->map_x] == 'O')
		draw_square_minimap(game, data->y, data->x, 0x799C00);
	else
		draw_square_minimap(game, data->y, data->x, 0xCCCCCC);
}

void	draw_mini_map(t_game *game)
{
	t_mini	data;

	data.start_x = (int)game->player.pos.x - MINI_VIEW_W / 2;
	data.start_y = (int)game->player.pos.y - MINI_VIEW_H / 2;
	data.y = 0;
	while (data.y < MINI_VIEW_H)
	{
		data.x = 0;
		while (data.x < MINI_VIEW_W)
		{
			data.map_x = data.start_x + data.x;
			data.map_y = data.start_y + data.y;
			if (data.map_x < 0 || data.map_x >= game->map.width - 1
				|| data.map_y < 0 || data.map_y >= game->map.height)
			{
				draw_square_minimap(game, data.y, data.x, 0x000000);
				data.x++;
				continue ;
			}
			check_case_draw(game, &data);
			data.x++;
		}
		data.y++;
	}
	draw_player_minimap(game);
}
