/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:21:01 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/24 13:11:37 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mouse(int x, int y, t_game *game)
{
	int		center_x;
	int		dx;
	double	rot;

	(void)y;
	center_x = IMAGE_WIDTH / 2;
	dx = x - center_x;
	rot = dx * game->player.rot_speed * 0.02;
	rotate_vector(&game->player.dir, rot);
	rotate_vector(&game->player.plane, rot);
	return (0);
}
