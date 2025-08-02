/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:58:26 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/02 18:58:26 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void calc_wall_dist(t_ray *r, t_player *p)
{
	if (r->hit_side == 0)
		r->dist = (r->map.x - p->pos.x + (1 - r->step.x) / 2) / r->dir.x;
	else
		r->dist = (r->map.y - p->pos.y + (1 - r->step.y) / 2) / r->dir.y;
}

void draw_wall_slice(t_game *d, t_ray *r, int x)
{
	int line_height;
	int draw_start;
	int draw_end;
	int color;

	line_height = (int)(IMAGE_HEIGHT / r->dist);
	draw_start = -line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_end >= IMAGE_HEIGHT)
		draw_end = IMAGE_HEIGHT - 1;
	if (r->hit_side == 0)
		color = 0xAAAAAA;
	else
		color = 0x888888;
	draw_vertical_line(d, x, draw_start, draw_end, color);
}

void draw_vertical_line(t_game *data, int x, int y_start, int y_end, int color)
{
	int y;

	y = y_start;
	while (y < y_end)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}