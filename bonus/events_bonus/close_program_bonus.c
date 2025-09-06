/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:42:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}

void	handle_exit(t_game *game)
{
	if (game->keys.esc)
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
