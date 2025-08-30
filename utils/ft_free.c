/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:17:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 10:52:09 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_map_data(t_game *data)
{
	int	i;

	if (data->map_lines)
	{
		i = 0;
		while (i < data->map_line_count && data->map_lines[i])
		{
			free(data->map_lines[i]);
			i++;
		}
		free(data->map_lines);
		data->map_lines = NULL;
		data->map.grid = NULL;
	}
	free_doors(data);
}

void	free_texture_paths(t_game *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i].path)
		{
			free(data->texture[i].path);
			data->texture[i].path = NULL;
		}
		if (data->player.anim[i].path)
		{
			free(data->player.anim[i].path);
			data->player.anim[i].path = NULL;
		}
		i++;
	}
	if (data->door_texture.path)
	{
		free(data->door_texture.path);
		data->door_texture.path = NULL;
	}
}

void	free_texture_images(t_game *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i].img && data->mlx.mlx_ptr)
		{
			mlx_destroy_image(data->mlx.mlx_ptr, data->texture[i].img);
			data->texture[i].img = NULL;
			data->texture[i].addr = NULL;
		}
		if (data->player.anim[i].img && data->mlx.mlx_ptr)
		{
			mlx_destroy_image(data->mlx.mlx_ptr, data->player.anim[i].img);
			data->player.anim[i].img = NULL;
			data->texture[i].addr = NULL;
		}
		i++;
	}
	if (data->door_texture.img && data->mlx.mlx_ptr)
	{
		mlx_destroy_image(data->mlx.mlx_ptr, data->door_texture.img);
		data->door_texture.img = NULL;
		data->door_texture.addr = NULL;
	}
}

void	free_texture_data(t_game *data)
{
	free_texture_paths(data);
	free_texture_images(data);
}
