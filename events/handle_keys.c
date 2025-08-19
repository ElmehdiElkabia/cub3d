/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:41:23 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 11:45:24 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_movement(int keycode, double *new_x, double *new_y,
		t_game *game)
{
	if (keycode == 119)
	{
		*new_x += game->player.dir.x * game->player.move_speed;
		*new_y += game->player.dir.y * game->player.move_speed;
	}
	if (keycode == 115)
	{
		*new_x -= game->player.dir.x * game->player.move_speed;
		*new_y -= game->player.dir.y * game->player.move_speed;
	}
	if (keycode == 97)
	{
		*new_x -= game->player.plane.x * game->player.move_speed;
		*new_y -= game->player.plane.y * game->player.move_speed;
	}
	if (keycode == 100)
	{
		*new_x += game->player.plane.x * game->player.move_speed;
		*new_y += game->player.plane.y * game->player.move_speed;
	}
}

static void	rotate_vector(t_vector *vec, double angle)
{
	double	old_x;

	old_x = vec->x;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = old_x * sin(angle) + vec->y * cos(angle);
}

static void	handle_rotation(int keycode, t_game *game)
{
	if (keycode == 65363)
	{
		rotate_vector(&game->player.dir, game->player.rot_speed);
		rotate_vector(&game->player.plane, game->player.rot_speed);
	}
	if (keycode == 65361)
	{
		rotate_vector(&game->player.dir, -game->player.rot_speed);
		rotate_vector(&game->player.plane, -game->player.rot_speed);
	}
}

void	update_new_pos(int keycode, double *new_x, double *new_y, t_game *game)
{
	handle_movement(keycode, new_x, new_y, game);
	handle_rotation(keycode, game);
}
