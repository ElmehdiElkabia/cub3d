/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:49:37 by marvin            #+#    #+#             */
/*   Updated: 2025/07/27 14:49:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int render_frame(t_game *data)
{
    // clear image buffer
    ft_bzero(data->img.addr, IMAGE_HIEGHT * IMAGE_WIDTH * (data->img.bpp / 8));

    // Draw 3D view

    // Optionally: draw minimap on top (debug)
	drawing_map(data);

    // put the image to the window
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->img.img, 0, 0);
    return (0);
}