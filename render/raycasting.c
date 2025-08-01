/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:16:19 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/01 03:40:46 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void raycasting(t_game *data)
{
	t_vector map_pos;
	t_vector delta_dist;
	t_vector ray_dir;
	t_vector side_dist;
	t_vector step;
	double camera_x;
	int x;

	x = 0;
	while (x < IMAGE_WIDTH)
	{
		camera_x = 2 * x / (double)IMAGE_WIDTH - 1;
		map_pos.x = (int)data->player.pos.x;
		map_pos.y = (int)data->player.pos.y;
		ray_dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		ray_dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		delta_dist.x = fabs(1 / ray_dir.x);
		delta_dist.y = fabs(1 / ray_dir.y);
		if (ray_dir.x < 0) // facing west
		{
			step.x = -1; // move west
			side_dist.x = (data->player.pos.x - map_pos.x) * delta_dist.x;
		}
		else // facing east
		{
			step.x = 1; // move east
			side_dist.x = (map_pos.x + 1.0 - data->player.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0) // facing north
		{
			step.y = -1; // move up
			side_dist.y = (data->player.pos.y - map_pos.y) * delta_dist.y;
		}
		else // facing south
		{
			step.y = 1; // move down
			side_dist.y = (map_pos.y + 1.0 - data->player.pos.y) * delta_dist.y;
		}

		int side = 0;

		while (data->map.grid[(int)map_pos.y][(int)map_pos.x] != '1')
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = 1;
			}
		}
		double perp_wall_dist;

		if (side == 0)
			perp_wall_dist = (map_pos.x - data->player.pos.x + (1 - step.x) / 2) / ray_dir.x; //(mapX - player.pos.x + (1 - stepX) / 2) / rayDirX;
		else
			perp_wall_dist = (map_pos.y - data->player.pos.y + (1 - step.y) / 2) / ray_dir.y; //(mapY - player.pos.y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(IMAGE_HIEGHT / perp_wall_dist);
		int drawStart = -lineHeight / 2 + IMAGE_HIEGHT / 2;
		int drawEnd = lineHeight / 2 + IMAGE_HIEGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		else if (drawStart > IMAGE_HIEGHT)
			drawStart = IMAGE_HIEGHT - 1;
		if (drawEnd < 0)
			drawEnd = 0;
		else if (drawEnd > IMAGE_HIEGHT)
			drawEnd = IMAGE_HIEGHT - 1;
		int y = 0;
		while (y < drawStart)
			my_mlx_pixel_put(&data->img, x, y++, 0x00ff00);
		y = drawStart;
		while (y < drawEnd)
			my_mlx_pixel_put(&data->img, x, y++, 0x0000ff);
		y = drawEnd;
		while (y < IMAGE_HIEGHT)
			my_mlx_pixel_put(&data->img, x, y++, 0xff0000);
		x++;
	}
}