/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:39:45 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == ' ' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == 'D')
		{
			while (line[i])
			{
				if (!is_valid_map_char(line[i]))
					return (0);
				i++;
			}
			return (1);
		}
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (0);
}

void	check_characters(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c))
				error_and_cleanup("Invalid character in map", game);
			x++;
		}
		y++;
	}
}

void	check_player(t_game *game)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count == 0)
		error_and_cleanup("No player found in map", game);
	if (player_count > 1)
		error_and_cleanup("Multiple player positions in map", game);
}
