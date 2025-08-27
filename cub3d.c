/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:18:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/24 12:29:35 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void    load_player_anim(t_game *game)
{
    char *paths[4] = {
        "texture/player/anim_0.xpm",
        "texture/player/anim_1.xpm",
        "texture/player/anim_2.xpm",
        "texture/player/anim_3.xpm"
    };
	int i = 0;
    while (i < 4)
    {
        game->player.anim[i].img = mlx_xpm_file_to_image(
            game->mlx.mlx_ptr,
            paths[i],
            &game->player.anim[i].width,
            &game->player.anim[i].height
        );
        if (!game->player.anim[i].img)
            printf("Failed to load %s\n", paths[i]);
        game->player.anim[i].addr = mlx_get_data_addr(
            game->player.anim[i].img,
            &game->player.anim[i].bpp,
            &game->player.anim[i].line_len,
            &game->player.anim[i].endian
        );
		i++;
    }
    game->player.frame = 0;
    game->player.frame_counter = 0;
    game->player.anim_playing = 0;
}

void    shouting(t_game *data)
{
    if (!data->player.anim_playing)
        return;

    data->player.frame_counter++;

    if (data->player.frame_counter >= 10)
    {
        data->player.frame++;
        data->player.frame_counter = 0;

        if (data->player.frame >= 4)
        {
            data->player.frame = 0;
            data->player.anim_playing = 0;
        }
    }
}
int    key_press_mouse(int button, int x, int y, void *param)
{
    (void)x;
    (void)y;
    t_game *data = (t_game *)param;
    if (button == 1)
        data->player.anim_playing = 1;
    return 0;
}

void handel_dor(t_game *data)
{
    int y = data->player.pos.y;
    int x = data->player.pos.x;

    int front_y = y + (int)round(data->player.dir.y);
    int front_x = x + (int)round(data->player.dir.x);


    if (data->map.grid[front_y][front_x] == 'D')
		data->map.grid[front_y][front_x] = 'O';

    else if (data->map.grid[front_y][front_x] == 'O')
		data->map.grid[front_y][front_x] = 'D';
}

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
		load_textures(&data);
		load_player_anim(&data);
		mlx_hook(data.mlx.win_ptr, 2, 1L << 0, key_press, &data);
		mlx_hook(data.mlx.win_ptr, 3, 1L << 1, key_release, &data);
		mlx_hook(data.mlx.win_ptr, 6, 1L << 6, handle_mouse, &data);
		mlx_hook(data.mlx.win_ptr, 17, 1L << 17, close_window, &data);
        mlx_mouse_hook(data.mlx.win_ptr, key_press_mouse, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, game_loop, &data);
		mlx_loop(data.mlx.mlx_ptr);
	}
}
