/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:09 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 12:13:35 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '\t' && line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	starts_with(char *line, char *id)
{
	int	i;
	int	j;

	if (!line | !id)
		return (0);
	i = 0;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] && id[j] && line[i] == id[j])
	{
		i++;
		j++;
	}
	if (id[j] == '\0' && (line[i] == ' ' || line[i] == '\t' || line[i] == '\0'
			|| line[i] == '\n'))
		return (1);
	return (0);
}

static void	handle_texture(char *line, t_game *game, int idx)
{
	if (game->in_map)
		error_and_cleanup("Error: Texture definition after map", game);
	parse_texture(line, game, idx);
}

static void	handle_color(char *line, t_game *game, int idx)
{
	if (game->in_map)
		error_and_cleanup("Error: Color definition after map", game);
	parse_colors(line, game, idx);
}

void	detect_type(char *line, t_game *game)
{
	if (starts_with(line, "NO"))
		handle_texture(line, game, 0);
	else if (starts_with(line, "SO"))
		handle_texture(line, game, 1);
	else if (starts_with(line, "WE"))
		handle_texture(line, game, 2);
	else if (starts_with(line, "EA"))
		handle_texture(line, game, 3);
	else if (starts_with(line, "F"))
		handle_color(line, game, 0);
	else if (starts_with(line, "C"))
		handle_color(line, game, 1);
	else if (game->in_map || is_map_line(line))
	{
		game->in_map = 1;
		parse_map(line, game);
	}
	else
		error_and_cleanup("Error: Invalid line format", game);
}

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
