/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:18:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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
		error_and_cleanup("Map allocation failed", game);
	game->map_line_count++;
}

void	check_map(t_game *game)
{
	if (game->map_line_count < 3)
		error_and_cleanup("Error: Map too small", game);
	if (game->map.width < 3)
		error_and_cleanup("Error: Map too small", game);
	check_characters(game);
	check_player(game);
	check_closure(game);
}

int	get_map_width(t_game *data)
{
	int	max_width;
	int	y;
	int	current_width;

	max_width = 0;
	y = 0;
	while (y < data->map.height)
	{
		current_width = (int)ft_strlen(data->map.grid[y]);
		if (current_width > max_width)
			max_width = current_width;
		y++;
	}
	return (max_width);
}
