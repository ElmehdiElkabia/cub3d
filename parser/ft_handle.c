/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:30:13 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/10 14:54:39 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		error_and_cleanup("Texture definition after map", game);
	parse_texture(line, game, idx);
}

static void	handle_color(char *line, t_game *game, int idx)
{
	if (game->in_map)
		error_and_cleanup("Color definition after map", game);
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
		error_and_cleanup("Invalid line format", game);
}
