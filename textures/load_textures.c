/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:54:19 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/19 17:19:09 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// hady rah ghadama heta newaslo logic dial recasting

// void load_textures(t_game *game)
// {
// 	int i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (!game->texture[i].path)
// 			print_error("Texture path is NULL");
// 		game->texture[i].img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
// 													 game->texture[i].path, &game->texture[i].width,
// 													 &game->texture[i].height);
// 		if (!game->texture[i].img)
// 			print_error("Failed to load texture image");
// 		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
// 												  &game->texture[i].bpp, &game->texture[i].line_len,
// 												  &game->texture[i].endian);
// 		if (!game->texture[i].addr)
// 			print_error("Failed to get texture data address");
// 		i++;
// 	}
// }
