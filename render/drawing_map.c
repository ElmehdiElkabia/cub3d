/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:58:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/19 17:17:45 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// hadchy ba9i khdam alih mat9isoch !!

#define TILE_SIZE 10

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_game *game, int grid_y, int grid_x, int color)
{
	int	py;
	int	px;
	int	start_x;
	int	start_y;

	start_x = grid_x * TILE_SIZE;
	start_y = grid_y * TILE_SIZE;
	py = 0;
	while (py < TILE_SIZE)
	{
		px = 0;
		while (px < TILE_SIZE)
		{
			my_mlx_pixel_put(&game->img, start_x + px, start_y + py, color);
			px++;
		}
		py++;
	}
}

void	draw_player(t_game *data)
{
	int	size;
	int	y;
	int	x;
	int	dy;
	int	dx;

	size = 5;
	y = data->player.pos.y * TILE_SIZE - size / 2;
	x = data->player.pos.x * TILE_SIZE - size / 2;
	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			my_mlx_pixel_put(&data->img, x + dx, y + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	drawing_map(t_game *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x] && x < (int)ft_strlen(data->map.grid[y]))
		{
			if (data->map.grid[y][x] == '1')
				draw_square(data, y, x, 0x333333);
			else if (data->map.grid[y][x] == '0' || data->map.grid[y][x] == ' ')
				draw_square(data, y, x, 0xCCCCCC);
			else if (ft_strchr("NSWE", data->map.grid[y][x]))
				draw_square(data, y, x, 0xCCCCCC);
			x++;
		}
		y++;
	}
	draw_player(data);
}
