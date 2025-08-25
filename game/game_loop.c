/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:46:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/25 11:38:37 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_sprite(t_game *game, t_texture *tex, int screen_x, int screen_y)
{
    int i, j;
    char *src;
    unsigned int color;

    for (j = 0; j < tex->height; j++)
    {
        for (i = 0; i < tex->width; i++)
        {
            src = tex->addr + (j * tex->line_len + i * (tex->bpp / 8));
            color = *(unsigned int *)src;

            // skip transparent pixels
            if ((color & 0x00FFFFFF) != 0)
                my_mlx_pixel_put(&game->img, screen_x + i, screen_y + j, color);
        }
    }
}

void draw_player_anim(t_game *game)
{
    t_texture *frame = &game->player.anim[game->player.frame];

    int screen_x = IMAGE_WIDTH / 2 - frame->width / 2;
    int screen_y = (IMAGE_HEIGHT - 250) - frame->height / 2;

    draw_sprite(game, frame, screen_x, screen_y);
}


static void	update_position(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player.pos.x);
	map_y = (int)(game->player.pos.y);
	if (game->map.grid[map_y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map.grid[(int)new_y][map_x] != '1')
		game->player.pos.y = new_y;
}

int	game_loop(t_game *game)
{
	double	new_x;
	double	new_y;

	handle_exit(game);
	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	handle_movement(&new_x, &new_y, game);
	handle_rotation(game);
	update_position(game, new_x, new_y);
	render_frame(game);
	return (0);
}
