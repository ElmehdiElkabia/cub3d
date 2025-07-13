/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:32:51 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/13 11:43:45 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int skip_identifier(char *line, int id)
{
	int i;
	char *type;

	i = 0;
	if (id == 0)
		type = "F";
	else if (id == 1)
		type = "C";
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

void parse_colors(char *line, t_game *game, int id)
{
	int i;
	char **colors;

	i = skip_identifier(line, id);
	if (i == -1)
		print_error("Invalid color line");
	colors = ft_split(line + i, ',');
	if (!colors)
		print_error("Malloc failed in parse_colors");
	if (id == 0)
	{
		game->map.floor.r = ft_atoi(colors[0]);
		game->map.floor.g = ft_atoi(colors[1]);
		game->map.floor.b = ft_atoi(colors[2]);
	}
	else if (id == 1)
	{
		game->map.ceiling.r = ft_atoi(colors[0]);
		game->map.ceiling.g = ft_atoi(colors[1]);
		game->map.ceiling.b = ft_atoi(colors[2]);
	}
}