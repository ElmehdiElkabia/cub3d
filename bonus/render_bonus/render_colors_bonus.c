/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:01:21 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	rgb_to_int(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

static void	get_colors(t_game *game, int *floor_color, int *ceiling_color)
{
	t_color	floor;
	t_color	ceiling;

	floor = game->map.floor;
	ceiling = game->map.ceiling;
	*floor_color = rgb_to_int(floor.r, floor.g, floor.b);
	*ceiling_color = rgb_to_int(ceiling.r, ceiling.g, ceiling.b);
}

static void	draw_ceiling(t_game *game, int x, int draw_start, int ceiling_color)
{
	int	y;

	y = 0;
	while (y < draw_start - 1)
		my_mlx_pixel_put(&game->img, x, y++, ceiling_color);
}

static void	draw_floor(t_game *game, int x, int draw_end, int floor_color)
{
	int	y;

	y = draw_end;
	while (y < IMAGE_HEIGHT - 1)
		my_mlx_pixel_put(&game->img, x, y++, floor_color);
}

void	draw_color(t_game *game, t_ray *ray, int x)
{
	int	floor_color;
	int	ceiling_color;
	int	line_height;
	int	draw_start;
	int	draw_end;

	get_colors(game, &floor_color, &ceiling_color);
	calculate_wall_dimensions(ray, &line_height, &draw_start, &draw_end);
	draw_ceiling(game, x, draw_start, ceiling_color);
	draw_floor(game, x, draw_end, floor_color);
}
