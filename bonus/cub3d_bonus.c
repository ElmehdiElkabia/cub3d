/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:18:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:02:36 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes_bonus/cub3d_bonus.h"

int	validate_file(char *filename)
{
	int	fd;
	int	len;

	if (!filename)
		print_error("Error: No filename provided");
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		print_error("Error: Map file must have .cub extension");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("Error: Cannot open map file");
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map_file.cub>"));
	if (!validate_file(argv[1]))
		return (1);
	init_game(&data);
	parser_file(argv[1], &data);
	set_player_direction(&data);
	init_minilibx(&data);
	load_textures(&data);
	mlx_hook(data.mlx.win_ptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_hook(data.mlx.win_ptr, 6, 1L << 6, handle_mouse, &data);
	mlx_hook(data.mlx.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_mouse_hook(data.mlx.win_ptr, key_press_mouse, &data);
	mlx_loop_hook(data.mlx.mlx_ptr, game_loop, &data);
	mlx_loop(data.mlx.mlx_ptr);
}
