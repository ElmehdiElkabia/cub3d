/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:44:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/28 14:54:28 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put_map(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 100 || y < 0 || y >= 100)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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
			my_mlx_pixel_put_map(&game->img, start_x + px, start_y + py, color);
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
			my_mlx_pixel_put_map(&game->img, px + dx, py + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void draw_mini_map(t_game *game)
{
    int start_x = (int)game->player.pos.x - MINI_VIEW_W / 2;
    int start_y = (int)game->player.pos.y - MINI_VIEW_H / 2;

    for (int y = 0; y < MINI_VIEW_H; y++)
    {
        for (int x = 0; x < MINI_VIEW_W; x++)
        {
            int map_x = start_x + x;
            int map_y = start_y + y;

            if (map_x < 0 || map_x >= game->map.width - 1 || map_y < 0 || map_y >= game->map.height)
            {
                draw_square_minimap(game, y, x, 0x000000);
                continue;
            }

            if (game->map.grid[map_y][map_x] == '1')
                draw_square_minimap(game, y, x, 0x333333);
			else if (game->map.grid[map_y][map_x] == 'D')
                draw_square_minimap(game, y, x, 0xF04000);
			else if (game->map.grid[map_y][map_x] == 'O')
                draw_square_minimap(game, y, x, 0x799C00);
            else
                draw_square_minimap(game, y, x, 0xCCCCCC);
        }
    }
    draw_player_minimap(game);
}