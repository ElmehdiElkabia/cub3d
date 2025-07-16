/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:02 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/16 20:19:14 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	// if (!mlx->mlx_ptr)
	// 	ft_destroy();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 999, 555, "Cub3D");
	// if (!mlx->win_ptr)
	// 	ft_destroy();
}

void	init_img(t_game *data)
{
	data->img.img = mlx_new_image(data->mlx.mlx_ptr, 999, 555);
	// if (!data->img.img)
	// 	ft_destroy();
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	// if (!data->img.addr)
	// 	ft_destroy();
}

void	init_minilibx(t_game *data)
{
	init_mlx(&data->mlx);
	init_img(data);
}
