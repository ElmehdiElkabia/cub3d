/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 09:49:47 by ayadouay          #+#    #+#             */
/*   Updated: 2025/09/02 09:49:55 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *g, int x, int y)
{
	char	c;

	if (y < 0 || x < 0 || y >= g->map.height || x >= g->map.width)
		return (1);
	c = g->map.grid[y][x];
	return (c == '1' || c == 'D');
}
