/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:03:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/13 11:26:41 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int skip_identifier(char *line, int id)
{
	int i;
	char *type;

	i = 0;
	if (id == 0)
		type = "NO";
	else if (id == 1)
		type = "SO";
	else if (id == 2)
		type = "WE";
	else
		type = "EA";
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (*type && line[i] == *type)
	{
		i++;
		type++;
	}
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (*type != '\0')
		return (-1);
	return (i);
}

void parse_texture(char *line, t_game *game, int id)
{
	int i;
	int path_start;

	if (game->texture[id].path)
		print_error("Texture defined more than once");
	i = skip_identifier(line, id);
	if (i == -1)
		print_error("Invalid texture line");
	path_start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	game->texture[id].path = ft_substr(line, path_start, i - path_start);
	if (!game->texture[id].path)
		print_error("Malloc failed in parse_texture");
}
