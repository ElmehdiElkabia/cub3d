/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:49:37 by marvin            #+#    #+#             */
/*   Updated: 2025/08/29 09:51:14 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	size;
	int	color;
	int	i;

	cx = IMAGE_WIDTH / 2;
	cy = IMAGE_HEIGHT / 2;
	size = 10;
	color = 0xFF0000;
	i = -size;
	while (i <= size)
	{
		my_mlx_pixel_put(&game->img, cx + i, cy, color);
		i++;
	}
	i = -size;
	while (i < size)
	{
		my_mlx_pixel_put(&game->img, cx, cy + i, color);
		i++;
	}
}

void	shouting(t_game *data)
{
	if (!data->player.anim_playing)
		return ;
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
	shouting(data);
	draw_player_anim(data);
	if(data->player.anim_playing == 0)
		draw_crosshair(data);
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
