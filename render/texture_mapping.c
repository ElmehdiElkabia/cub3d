/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:34:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 11:32:01 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_texture	*select_texture(t_game *data, t_ray *r)
{
	if (r->side == 0 && r->dir.x < 0)
		return (&data->texture[EAST]);
	else if (r->side == 0 && r->dir.x > 0)
		return (&data->texture[WEST]);
	else if (r->side == 1 && r->dir.y < 0)
		return (&data->texture[NORTH]);
	else
		return (&data->texture[SOUTH]);
}

static int	calculate_texture_x(t_texture *texture, t_ray *r, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if ((r->side == 0 && r->dir.x > 0) || (r->side == 1 && r->dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	draw_textured_vertical_line(t_game *data, t_texture *texture, int x,
		t_tex_vars value)
{
	t_draw_vars	vars;

	vars.y = value.draw_start;
	vars.step = 1.0 * texture->height / value.line_height;
	vars.tex_pos = (value.draw_start - IMAGE_HEIGHT / 2 + value.line_height / 2)
		* vars.step;
	while (vars.y < value.draw_end)
	{
		vars.tex_y = (int)vars.tex_pos & (texture->height - 1);
		vars.tex_pos += vars.step;
		vars.pixel = texture->addr + (vars.tex_y * texture->line_len
				+ value.tex_x * (texture->bpp / 8));
		vars.color = *(unsigned int *)vars.pixel;
		my_mlx_pixel_put(&data->img, x, vars.y, vars.color);
		vars.y++;
	}
}

void	texture_mapping(t_game *data, t_ray *r, int x)
{
	t_tex_vars	vars;

	vars.wall_x = calculate_wall_position(data, r);
	vars.texture = select_texture(data, r);
	vars.tex_x = calculate_texture_x(vars.texture, r, vars.wall_x);
	calculate_wall_dimensions(r, &vars.line_height, &vars.draw_start,
		&vars.draw_end);
	draw_textured_vertical_line(data, vars.texture, x, vars);
}
