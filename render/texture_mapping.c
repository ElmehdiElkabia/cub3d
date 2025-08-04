/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:34:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/04 16:11:54 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_textured_vertical_line(t_game *data, t_texture *texture, int x, int tex_x, int draw_start, int draw_end, int line_height)
{
	int y = draw_start;
	double step = 1.0 * texture->height / line_height;
	double tex_pos = (draw_start - IMAGE_HEIGHT / 2 + line_height / 2) * step;

	while (y < draw_end)
	{
		int tex_y = (int)tex_pos & (texture->height - 1); // texture height must be power of 2
		tex_pos += step;

		char *pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
		int color = *(unsigned int *)pixel;
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

void texture_mapping(t_game *data, t_ray *r, int x)
{
	double wall_x;
	t_texture *texture;

	// 1. Determine wall hit position
	if (r->hit_side == 0)
		wall_x = data->player.pos.y + r->dist * r->dir.y;
	else
		wall_x = data->player.pos.x + r->dist * r->dir.x;
	wall_x -= floor(wall_x);

	// 2. Choose correct texture based on hit direction
	if (r->hit_side == 0 && r->dir.x < 0)
		texture = &data->texture[EAST];
	else if (r->hit_side == 0 && r->dir.x > 0)
		texture = &data->texture[WEST];
	else if (r->hit_side == 1 && r->dir.y < 0)
		texture = &data->texture[NORTH];
	else
		texture = &data->texture[SOUTH];

	// 3. Compute X coordinate in texture
	int tex_x = (int)(wall_x * (double)texture->width);
	if ((r->hit_side == 0 && r->dir.x > 0) || (r->hit_side == 1 && r->dir.y < 0))
		tex_x = texture->width - tex_x - 1;

	// if (r->dist < 0.001)
	// 	r->dist = 0.001;
	// printf("dir %f\n", r->dist);
	// 4. Compute vertical slice dimensions
	int line_height = (int)(IMAGE_HEIGHT / r->dist);
	int draw_start = -line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + IMAGE_HEIGHT / 2;
	if (draw_end >= IMAGE_HEIGHT)
		draw_end = IMAGE_HEIGHT - 1;
	// 5. Draw textured slice
	draw_textured_vertical_line(data, texture, x, tex_x, draw_start, draw_end, line_height);
}