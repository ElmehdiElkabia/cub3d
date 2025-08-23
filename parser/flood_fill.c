/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:16:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/22 11:12:54 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**duplicate_map(char **original)
{
	int		i;
	int		j;
	char	**copy;

	i = ft_strlen(*original);
	j = 0;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		print_error("Failed to allocate map copy");
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		while (copy[i][j])
		{
			if (copy[i][j] == 'N' || copy[i][j] == 'S' || copy[i][j] == 'E'
				|| copy[i][j] == 'W')
				copy[i][j] = '0';
			j++;
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	find_player_position(char **map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
	print_error("Player not found when trying to locate spawn point");
}

void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		print_error("Map is not closed");
	if (map[y][x] == ' ' || map[y][x] == '\0')
		print_error("Map is not closed");
	if (map[y][x] != '0' && map[y][x] != '1')
		return ;
	if (map[y][x] == '1')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
