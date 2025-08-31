/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:21:01 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/31 09:15:35 by ayadouay         ###   ########.fr       */
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
		if (game->keys.mouse_fixed == 1)
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
