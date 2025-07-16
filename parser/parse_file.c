/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:09 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/16 20:14:19 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_empty_line(char *line)
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

void	detect_type(char *line, t_game *game)
{
	if (starts_with(line, "NO"))
		parse_texture(line, game, 0);
	else if (starts_with(line, "SO"))
		parse_texture(line, game, 1);
	else if (starts_with(line, "WE"))
		parse_texture(line, game, 2);
	else if (starts_with(line, "EA"))
		parse_texture(line, game, 3);
	else if (starts_with(line, "F"))
		parse_colors(line, game, 0);
	else if (starts_with(line, "C"))
		parse_colors(line, game, 1);
	else if (game->in_map || is_map_line(line))
	{
		game->in_map = 1;
		parse_map(line, game);
	}
	else
		printf("unknown line: %s\n", line);
}

void	*parser_file(char *file, t_game *game)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		detect_type(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->map.grid = game->map_lines;
	game->map.height = game->map_line_count;
	check_map(game);
	return (NULL);
}
