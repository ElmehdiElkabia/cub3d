/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:18:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:21:53 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map_file.cub>"));
	else
	{
		init_game(&data);
		parser_file(argv[1], &data);
		set_player_direction(&data);
		init_minilibx(&data);
		mlx_hook(data.mlx.win_ptr, 2, 1L << 0, update_player, &data);
		mlx_hook(data.mlx.win_ptr, 17, 1L << 17, close_window, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, render_frame, &data);
		mlx_loop(data.mlx.mlx_ptr);
	}
}
