/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:18:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/19 11:57:25 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


int main(int argc, char **argv)
{
	t_game data;

	if (argc != 2) // || check_filename(argv[1])
		return (print_error("Usage: ./cub3D <map_file.cub>"));
	else
	{

		// 1. Init game struct (zero it)
		init_game(&data);
		// 2. Parse the .cub file → fill data.map, data.textures, data.floor/ceiling
		parser_file(argv[1], &data);
		// 3. Set player position & direction
		set_player_direction(&data);
		// 4. Init MiniLibX (mlx, window, image buffer)
		init_minilibx(&data);

		// 5. Start rendering loop (mlx_loop_hook / mlx_loop)
		mlx_loop(data.mlx.mlx_ptr);
		// 6. On exit, free all resources
	}
}
