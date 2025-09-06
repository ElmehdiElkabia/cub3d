/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 19:34:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static t_texture	*select_texture(t_game *data, t_ray *r)
{
	if (data->map.grid[(int)r->map.y][(int)r->map.x] == 'D')
		return (&data->door_texture);
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

	if (data->map.grid[(int)r->map.y][(int)r->map.x] == 'D')
	{
		draw_door(data, r, x);
		return ;
	}
	vars.wall_x = calculate_wall_position(data, r);
	vars.texture = select_texture(data, r);
	vars.tex_x = calculate_texture_x(vars.texture, r, vars.wall_x);
	calculate_wall_dimensions(r, &vars.line_height, &vars.draw_start,
		&vars.draw_end);
	draw_textured_vertical_line(data, vars.texture, x, vars);
}

void	draw_door(t_game *data, t_ray *r, int x)
{
	t_tex_vars	vars;
	t_door		*door;
	double		door_offset;

	door = get_door_at(data, (int)r->map.x, (int)r->map.y);
	vars.wall_x = calculate_wall_position(data, r);
	vars.texture = &data->door_texture;
	if (door && door->state != DOOR_CLOSED)
	{
		door_offset = door->anim_progress;
		if (r->side == 0)
			vars.wall_x += door_offset;
		else
			vars.wall_x += door_offset;
	}
	vars.tex_x = calculate_texture_x(vars.texture, r, vars.wall_x);
	calculate_wall_dimensions(r, &vars.line_height, &vars.draw_start,
		&vars.draw_end);
	if (door && (door->state == DOOR_OPENING || door->state == DOOR_CLOSING))
	{
		vars.draw_end = vars.draw_start + (int)(vars.line_height * (1.0
					- door->anim_progress * 0.5));
	}
	draw_textured_vertical_line(data, vars.texture, x, vars);
}
