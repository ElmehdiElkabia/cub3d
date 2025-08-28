/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:16:19 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/28 13:53:10 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_step_side(t_game *data, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (data->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - data->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (data->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - data->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	init_ray(t_game *data, t_ray *ray, int x)
{
	double	camera;

	camera = 2 * x / (double)IMAGE_WIDTH - 1;
	ray->dir.x = data->player.dir.x + data->player.plane.x * camera;
	ray->dir.y = data->player.dir.y + data->player.plane.y * camera;
	ray->map.x = (int)data->player.pos.x;
	ray->map.y = (int)data->player.pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	perform_dda(t_game *data, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->map.grid[(int)ray->map.y][(int)ray->map.x] == '1' ||
			data->map.grid[(int)ray->map.y][(int)ray->map.x] == 'D')
			break ;
	}
}

void	raycasting(t_game *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < IMAGE_WIDTH)
	{
		init_ray(data, &ray, x);
		calculate_step_side(data, &ray);
		perform_dda(data, &ray);
		calculate_distance(&ray);
		texture_mapping(data, &ray, x);
		draw_color(data, &ray, x);
		x++;
	}
}
