/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:16:49 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/24 20:12:49 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	replace_player_with_zero(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
			|| line[j] == 'W')
			line[j] = '0';
		j++;
	}
}

char	**duplicate_map(char **original)
{
	int		i;
	int		map_height;
	char	**copy;

	map_height = 0;
	while (original[map_height])
		map_height++;
	copy = malloc(sizeof(char *) * (map_height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			return (free(copy), NULL);
		}
		replace_player_with_zero(copy[i]);
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

void	flood_fill_recursive(char **map, int x, int y, int *error_flag)
{
	if (*error_flag)
		return ;
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
	{
		*error_flag = 1;
		return ;
	}
	if (map[y][x] == ' ' || map[y][x] == '\0')
	{
		*error_flag = 1;
		return ;
	}
	if (map[y][x] != '0' && map[y][x] != '1')
		return ;
	if (map[y][x] == '1')
		return ;
	map[y][x] = 'F';
	flood_fill_recursive(map, x + 1, y, error_flag);
	flood_fill_recursive(map, x - 1, y, error_flag);
	flood_fill_recursive(map, x, y + 1, error_flag);
	flood_fill_recursive(map, x, y - 1, error_flag);
}

void	flood_fill(char **map, int x, int y)
{
	int	error_flag;

	error_flag = 0;
	flood_fill_recursive(map, x, y, &error_flag);
	if (error_flag)
	{
		ft_free_split(map);
		print_error("Map is not closed");
	}
}
