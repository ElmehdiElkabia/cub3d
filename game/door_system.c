/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:58:15 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 10:58:26 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handel_dor(t_game *data)
{
	int	y;
	int	x;
	int	front_y;
	int	front_x;

	y = data->player.pos.y;
	x = data->player.pos.x;
	front_y = y + (int)round(data->player.dir.y);
	front_x = x + (int)round(data->player.dir.x);
	if (data->map.grid[front_y][front_x] == 'D')
		data->map.grid[front_y][front_x] = 'O';
	else if (data->map.grid[front_y][front_x] == 'O')
		data->map.grid[front_y][front_x] = 'D';
}
