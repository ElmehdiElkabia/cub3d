/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:58:26 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:15:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void	calculate_wall_dimensions(t_ray *r, int *line_height, int *draw_start,
		int *draw_end)
{
	*line_height = (int)(IMAGE_HEIGHT / r->perp_wall_dist);
	*draw_start = -*line_height / 2 + IMAGE_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *line_height / 2 + IMAGE_HEIGHT / 2;
	if (*draw_end >= IMAGE_HEIGHT)
		*draw_end = IMAGE_HEIGHT - 1;
}

double	calculate_wall_position(t_game *data, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = data->player.pos.y + r->perp_wall_dist * r->dir.y;
	else
		wall_x = data->player.pos.x + r->perp_wall_dist * r->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
