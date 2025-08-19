/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:28:53 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		print_error("mlx init failed");
		exit(1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT,
			"Cub3D");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		print_error("Window init failed");
		exit(1);
	}
}

void	init_img(t_game *data)
{
	data->img.img = mlx_new_image(data->mlx.mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!data->img.img)
	{
		destroy_mlx(data);
		print_error("Image init failed");
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
	{
		destroy_img(data);
		destroy_mlx(data);
		print_error("Image addr failed");
		exit(1);
	}
}

void	init_minilibx(t_game *data)
{
	init_mlx(&data->mlx);
	init_img(data);
}
