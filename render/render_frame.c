/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:49:37 by marvin            #+#    #+#             */
/*   Updated: 2025/08/24 12:45:56 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_frame(t_game *data)
{
	if (!data->img.img)
	{
		data->img.img = mlx_new_image(data->mlx.mlx_ptr, IMAGE_WIDTH,
				IMAGE_HEIGHT);
		if (!data->img.img)
			return (1);
		data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
				&data->img.line_len, &data->img.endian);
	}
	ft_bzero(data->img.addr, IMAGE_HEIGHT * IMAGE_WIDTH * (data->img.bpp / 8));
	raycasting(data);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->img.img,
		0, 0);
	mlx_mouse_move(data->mlx.mlx_ptr, data->mlx.win_ptr, IMAGE_WIDTH / 2,
		IMAGE_HEIGHT / 2);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= IMAGE_WIDTH || y < 0 || y >= IMAGE_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
