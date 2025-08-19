/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:42:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:49:48 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

void	handle_exit(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		cleanup_and_exit(game, 0);
	}
}

void	cleanup_and_exit(t_game *data, int exit_code)
{
	destroy_img(data);
	free_texture_data(data);
	destroy_mlx(data);
	free_map_data(data);
	exit(exit_code);
}
