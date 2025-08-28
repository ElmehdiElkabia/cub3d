/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:21:01 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/28 13:56:16 by eelkabia         ###   ########.fr       */
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
	if (dx != 0)
	{
		rot = dx * game->player.rot_speed * 0.02;
		rotate_vector(&game->player.dir, rot);
		rotate_vector(&game->player.plane, rot);
		mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, center_x,
			IMAGE_HEIGHT / 2);
	}
	return (0);
}

int	key_press_mouse(int button, int x, int y, void *param)
{
	t_game	*data;

	(void)x;
	(void)y;
	data = (t_game *)param;
	if (button == 1)
		data->player.anim_playing = 1;
	return (0);
}
