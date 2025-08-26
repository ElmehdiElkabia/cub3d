/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:54:19 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/26 16:21:55 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	load_single_player_anim(t_game *game, int i, char *path)
{
	game->player.anim[i].img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			path, &game->player.anim[i].width,
			&game->player.anim[i].height);
	if (!game->player.anim[i].img)
		printf("Failed to load %s\n", path);
	game->player.anim[i].addr = mlx_get_data_addr(game->player.anim[i].img,
			&game->player.anim[i].bpp, &game->player.anim[i].line_len,
			&game->player.anim[i].endian);
}

void	load_player_anim(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = "texture/player/anim_0.xpm";
	paths[1] = "texture/player/anim_1.xpm";
	paths[2] = "texture/player/anim_2.xpm";
	paths[3] = "texture/player/anim_3.xpm";
	i = 0;
	while (i < 4)
	{
		load_single_player_anim(game, i, paths[i]);
		i++;
	}
	game->player.frame = 0;
	game->player.frame_counter = 0;
	game->player.anim_playing = 0;
}

static void	load_single_texture(t_game *game, int i)
{
	if (!game->texture[i].path)
	{
		cleanup_and_exit(game, 1);
	}
	if (!game->texture[i].img)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
				game->texture[i].path, &game->texture[i].width,
				&game->texture[i].height);
		if (!game->texture[i].img)
		{
			print_error("Failed to load texture image");
			cleanup_and_exit(game, 1);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bpp, &game->texture[i].line_len,
				&game->texture[i].endian);
		if (!game->texture[i].addr)
		{
			print_error("Failed to get texture data address");
			cleanup_and_exit(game, 1);
		}
	}
}

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		load_single_texture(game, i);
		i++;
	}
	load_player_anim(game);
}
