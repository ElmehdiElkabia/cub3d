/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:16:19 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/21 11:52:36 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_ray(t_game *d, t_ray *r, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)IMAGE_WIDTH - 1;
	r->dir.x = d->player.dir.x + d->player.plane.x * camera_x;
	r->dir.y = d->player.dir.y + d->player.plane.y * camera_x;
	r->map.x = (int)d->player.pos.x;
	r->map.y = (int)d->player.pos.y;
	r->delta.x = fabs(1 / r->dir.x);
	r->delta.y = fabs(1 / r->dir.y);
}

void calc_step(t_ray *r, t_player *p)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side.x = (p->pos.x - r->map.x) * r->delta.x;
	}
	else
	{
		r->step.x = 1;
		r->side.x = (r->map.x + 1.0 - p->pos.x) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side.y = (p->pos.y - r->map.y) * r->delta.y;
	}
	else
	{
		r->step.y = 1;
		r->side.y = (r->map.y + 1.0 - p->pos.y) * r->delta.y;
	}
}

void perform_dda(t_game *d, t_ray *r)
{
	while (1)
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->map.x += r->step.x;
			r->hit_side = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->map.y += r->step.y;
			r->hit_side = 1;
		}
		if (d->map.grid[(int)r->map.y][(int)r->map.x] == '1')
			break;
	}
}

void raycasting(t_game *data)
{
	t_ray ray;
	int x;

	x = 0;
	while (x < IMAGE_WIDTH)
	{
		init_ray(data, &ray, x);
		calc_step(&ray, &data->player);
		perform_dda(data, &ray);
		calc_wall_dist(&ray, &data->player);
		texture_mapping(data, &ray, x);
		draw_color(data, &ray, x);
		// draw_wall_slice(data, &ray, x);
		x++;
	}
}
