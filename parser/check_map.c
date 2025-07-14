/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:09:07 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/14 17:08:46 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == ' ' ||
			*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			return (1);
		line++;
	}
	return (0);
}

int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || 
			c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
			c == ' ' || c == '\n' );
}

void	check_characters(t_game *game)
{
	int	y;
	int	x;
	char	c;
	
	y = 0;
	while (y < game->map_line_count)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			// printf("c ==> %c (%d)\n", c, c);
			if (!is_valid_map_char(c))
				print_error("Invalid character in map");
			x++;
		}
		y++;
	}
}


void check_map(t_game *game)
{
	check_characters(game);
	//check_player(game);     // exactly one player, store its position
	//check_closure(game);    // wall check (flood fill or border check)
}
