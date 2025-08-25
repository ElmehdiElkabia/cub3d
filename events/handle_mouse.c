/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:21:01 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/25 09:10:42 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mouse(int x, int y, t_game *game)
{
    int center_x = IMAGE_WIDTH / 2;
    int dx;
    (void)y;
    dx = x - center_x;

    double rot = dx * 0.002;

    // rotate right if dx positive, left if negative
    double old_dir_x = game->player.dir.x;
    game->player.dir.x = game->player.dir.x * cos(rot) - game->player.dir.y * sin(rot);
    game->player.dir.y = old_dir_x * sin(rot) + game->player.dir.y * cos(rot);

    double old_plane_x = game->player.plane.x;
    game->player.plane.x = game->player.plane.x * cos(rot) - game->player.plane.y * sin(rot);
    game->player.plane.y = old_plane_x * sin(rot) + game->player.plane.y * cos(rot);

	(void)y;
	center_x = IMAGE_WIDTH / 2;
	dx = x - center_x;
	rot = dx * game->player.rot_speed * 0.02;
	rotate_vector(&game->player.dir, rot);
	rotate_vector(&game->player.plane, rot);
	return (0);
}
