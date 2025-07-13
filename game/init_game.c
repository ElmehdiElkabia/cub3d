/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:20:18 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/13 12:20:43 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	// if (!mlx->mlx_ptr)
	// 	ft_destroy();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 100, 100, "Cub3D");
	// if (!mlx->win_ptr)
	// 	ft_destroy();
}

void init_img(t_game *data)
{
	data->img.img = mlx_new_image(data->mlx.mlx_ptr, 100, 100);
	// if (!data->img.img)
	// 	ft_destroy();
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	// if (!data->img.addr)
	// 	ft_destroy();
}

void init_map(t_map *map)
{
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->ceiling.r = 0;
	map->ceiling.g = 0;
	map->ceiling.b = 0;
}

void init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->move_speed = 0;
	player->rot_speed = 0;
}

void init_texture(t_game *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].path = NULL;
		data->texture[i].img = NULL;
		data->texture[i].addr = NULL;
		data->texture[i].width = 0;
		data->texture[i].height = 0;
		data->texture[i].bpp = 0;
		data->texture[i].line_len = 0;
		data->texture[i].endian = 0;
		i++;
	}
}

void init_game(t_game *data)
{
	ft_bzero(data, sizeof(t_game));
	init_mlx(&data->mlx);
	init_img(data);
	init_map(&data->map);
	init_player(&data->player);
	init_texture(data);
}