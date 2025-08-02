/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:58:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/26 16:37:07 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// hadchy ba9i khdam alih mat9isoch !!

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / MINI_MAP));
	*(unsigned int *)dst = color;
}

void draw_square(t_game *game, int grid_y, int grid_x, int color)
{
	int py;
	int px;
	int start_x;
	int start_y;

	start_x = grid_x * MINI_MAP;
	start_y = grid_y * MINI_MAP;
	py = 0;
	while (py < MINI_MAP)
	{
		px = 0;
		while (px < MINI_MAP)
		{
			my_mlx_pixel_put(&game->img, start_x + px, start_y + py, color);
			px++;
		}
		py++;
	}
}

void draw_player(t_game *data)
{
	int size;
	int y;
	int x;
	int dy;
	int dx;

	size = 5;
	y = data->player.pos.y * MINI_MAP - size / 2;
	x = data->player.pos.x * MINI_MAP - size / 2;
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

void draw_grid_lines(t_game *data)
{
	int x;
	int y;
	int px;
	int py;

	// Draw vertical lines
	x = 0;
	while (x <= data->map.width * MINI_MAP)
	{
		py = 0;
		while (py < data->map.height * MINI_MAP)
		{
			my_mlx_pixel_put(&data->img, x, py, 0x000000); // black grid lines
			py++;
		}
		x += MINI_MAP;
	}
	// Draw horizontal lines
	y = 0;
	while (y <= data->map.height * MINI_MAP)
	{
		px = 0;
		while (px < data->map.width * MINI_MAP)
		{
			my_mlx_pixel_put(&data->img, px, y, 0x000000); // black grid lines
			px++;
		}
		y += MINI_MAP;
	}
}

void drawing_map(t_game *data)
{
	int y;
	int x;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x] && x < data->map.width)
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
	draw_grid_lines(data);
	draw_player(data);
	draw_fov(data);
}
