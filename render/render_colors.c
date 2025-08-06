/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:01:21 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/04 17:57:04 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
}

void draw_color(t_game *game, t_ray *ray, int x)
{
	t_color floor;
	t_color ceiling;

	floor = game->map.floor;
	ceiling = game->map.ceiling;
	int floor_color = rgb_to_int(floor.r, floor.g, floor.b);
	int ceiling_color = rgb_to_int(ceiling.r, ceiling.g, ceiling.b);

	if (ray->dist < 0.0001)
		ray->dist = 0.0001;

	int line_height = (int)(IMAGE_HEIGHT / ray->dist);
	int draw_start = -line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_end >= IMAGE_HEIGHT)
		draw_end = IMAGE_HEIGHT - 1;

	int y = 0;
	while (y < draw_start -1)
		my_mlx_pixel_put(&game->img, x, y++, ceiling_color);
	y = draw_end;
	while (y < IMAGE_HEIGHT -1)
		my_mlx_pixel_put(&game->img, x, y++, floor_color);
}