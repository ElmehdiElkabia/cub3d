/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:32:51 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 10:57:16 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	skip_identifier(char *line, int id)
{
	int		i;
	char	*type;

	i = 0;
	if (id == 0)
		type = "F";
	else if (id == 1)
		type = "C";
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != *type)
		return (-1);
	i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	get_color(char **colors, t_game *game, int id)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_split(colors);
		error_and_cleanup("Color value out of range", game);
	}
	if (id == 0)
	{
		game->map.floor.r = r;
		game->map.floor.g = g;
		game->map.floor.b = b;
	}
	else if (id == 1)
	{
		game->map.ceiling.r = r;
		game->map.ceiling.g = g;
		game->map.ceiling.b = b;
	}
}

int	check_color(char **colors)
{
	int (slot), (i);
	slot = 0;
	while (colors[slot])
	{
		i = 0;
		while (colors[slot][i] == ' ' || colors[slot][i] == '\t')
			i++;
		if (colors[slot][i] == '\0')
			return (1);
		while (colors[slot][i])
		{
			if (colors[slot][i] == ' ' || colors[slot][i] == '\t'
				|| colors[slot][i] == '\n')
			{
				i++;
				continue ;
			}
			if (colors[slot][i] < '0' || colors[slot][i] > '9')
				return (1);
			i++;
		}
		slot++;
	}
	return (0);
}

void	parse_colors(char *line, t_game *game, int id)
{
	int		i;
	char	**colors;

	i = skip_identifier(line, id);
	if (i == -1)
		error_and_cleanup("Invalid color line", game);
	colors = ft_split(line + i, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		ft_free_split(colors);
		error_and_cleanup("Invalid color format (must be R,G,B)", game);
	}
	if (check_color(colors))
	{
		ft_free_split(colors);
		error_and_cleanup("Invalid color (must be number)", game);
	}
	get_color(colors, game, id);
	ft_free_split(colors);
}
