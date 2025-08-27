/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:17:55 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/27 18:51:30 by ayadouay         ###   ########.fr       */
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
}

void	free_texture_data(t_game *data)
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
		if (data->texture[i].img && data->mlx.mlx_ptr)
		{
			mlx_destroy_image(data->mlx.mlx_ptr, data->texture[i].img);
			data->texture[i].img = NULL;
			data->texture[i].addr = NULL;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (data->player.anim[i].path)
		{
			free(data->player.anim[i].path);
			data->player.anim[i].path = NULL;
		}
		if (data->player.anim[i].img && data->mlx.mlx_ptr)
		{
			mlx_destroy_image(data->mlx.mlx_ptr, data->player.anim[i].img);
			data->player.anim[i].img = NULL;
			data->player.anim[i].addr = NULL;
		}
		i++;
	}
	
}
