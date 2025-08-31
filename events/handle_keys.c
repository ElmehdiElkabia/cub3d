/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:41:23 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/31 09:17:16 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 1;
	else if (keycode == 115)
		game->keys.s = 1;
	else if (keycode == 97)
		game->keys.a = 1;
	else if (keycode == 100)
		game->keys.d = 1;
	else if (keycode == 65361)
		game->keys.left = 1;
	else if (keycode == 65363)
		game->keys.right = 1;
	else if (keycode == 65307)
		game->keys.esc = 1;
	else if (keycode == 101)
		handel_dor(game);
	else if (keycode == 65505)
		game->keys.mouse_fixed = 0;
	else if (keycode == 65509)
		game->keys.mouse_fixed = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->keys.w = 0;
	else if (keycode == 115)
		game->keys.s = 0;
	else if (keycode == 97)
		game->keys.a = 0;
	else if (keycode == 100)
		game->keys.d = 0;
	else if (keycode == 65361)
		game->keys.left = 0;
	else if (keycode == 65363)
		game->keys.right = 0;
	else if (keycode == 65307)
		game->keys.esc = 0;
	return (0);
}

void	handle_movement(double *new_x, double *new_y, t_game *game)
{
	if (game->keys.w)
	{
		*new_x += game->player.dir.x * game->player.move_speed;
		*new_y += game->player.dir.y * game->player.move_speed;
	}
	if (game->keys.s)
	{
		*new_x -= game->player.dir.x * game->player.move_speed;
		*new_y -= game->player.dir.y * game->player.move_speed;
	}
	if (game->keys.a)
	{
		*new_x -= game->player.plane.x * game->player.move_speed;
		*new_y -= game->player.plane.y * game->player.move_speed;
	}
	if (game->keys.d)
	{
		*new_x += game->player.plane.x * game->player.move_speed;
		*new_y += game->player.plane.y * game->player.move_speed;
	}
}

void	rotate_vector(t_vector *vec, double angle)
{
	double	old_x;

	old_x = vec->x;
	vec->x = old_x * cos(angle) - vec->y * sin(angle);
	vec->y = old_x * sin(angle) + vec->y * cos(angle);
}

void	handle_rotation(t_game *game)
{
	if (game->keys.right)
	{
		rotate_vector(&game->player.dir, game->player.rot_speed);
		rotate_vector(&game->player.plane, game->player.rot_speed);
	}
	if (game->keys.left)
	{
		rotate_vector(&game->player.dir, -game->player.rot_speed);
		rotate_vector(&game->player.plane, -game->player.rot_speed);
	}
}
