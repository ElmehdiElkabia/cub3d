/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:18:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/16 20:14:47 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**append_map_line(char **old, char *new_line, int size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = old[i];
		i++;
	}
	new[i++] = ft_strdup(new_line);
	new[i] = NULL;
	free(old);
	return (new);
}

void	print_map(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		printf("%s\n", grid[i]);
		i++;
	}
}

void	parse_map(char *line, t_game *game)
{
	game->map_lines = append_map_line(game->map_lines, line,
			game->map_line_count);
	if (!game->map_lines)
		print_error("Map allocation failed");
	game->map_line_count++;
}

void	check_map(t_game *game)
{
	check_characters(game);
	check_player(game);
	check_closure(game);
}
