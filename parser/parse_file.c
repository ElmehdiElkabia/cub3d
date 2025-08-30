/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:09 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 12:30:30 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	parse_line(char *line, t_game *game, int *has_content)
{
	if (is_empty_line(line))
		return ;
	*has_content = 1;
	detect_type(line, game);
}

static void	validate_required_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!game->texture[i].path)
			error_and_cleanup("Error: Missing texture", game);
		i++;
	}
	if (game->map.floor.r == -1)
		error_and_cleanup("Error: Missing floor color", game);
	if (game->map.ceiling.r == -1)
		error_and_cleanup("Error: Missing ceiling color", game);
	if (game->map_line_count == 0)
		error_and_cleanup("Error: Map missing", game);
}

static void	check_map_content_order(char *line, int *map_started,
		int *map_ended, t_game *game)
{
	if (!is_empty_line(line))
	{
		if (is_map_line(line))
		{
			if (*map_ended)
				error_and_cleanup("Error: Map content after map ended", game);
			*map_started = 1;
		}
		else if (*map_started)
			error_and_cleanup("Error: Non-map content after map started", game);
	}
	else if (*map_started && !*map_ended)
		*map_ended = 1;
}

static void	validate_file_content(char *file, t_game *game)
{
	char	*line;
	int		fd;
	int		has_content;
	int		map_started;
	int		map_ended;

	has_content = 0;
	map_started = 0;
	map_ended = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_and_cleanup("Error: Cannot open file", game);
	line = get_next_line(fd);
	while (line)
	{
		check_map_content_order(line, &map_started, &map_ended, game);
		parse_line(line, game, &has_content);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!has_content)
		error_and_cleanup("Error: Map file is empty", game);
}

void	*parser_file(char *file, t_game *game)
{
	validate_file_content(file, game);
	validate_required_elements(game);
	game->map.grid = game->map_lines;
	game->map.height = game->map_line_count;
	game->map.width = get_map_width(game);
	check_map(game);
	init_doors(game);
	return (NULL);
}
