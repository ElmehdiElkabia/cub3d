/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:23:09 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 12:47:04 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_img(t_game *data)
{
	if (data->img.img && data->mlx.mlx_ptr)
	{
		mlx_destroy_image(data->mlx.mlx_ptr, data->img.img);
		data->img.img = NULL;
		data->img.addr = NULL;
	}
}

void	destroy_mlx(t_game *data)
{
	if (data->mlx.win_ptr)
	{
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
		data->mlx.win_ptr = NULL;
	}
	if (data->mlx.mlx_ptr)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
		data->mlx.mlx_ptr = NULL;
	}
}
