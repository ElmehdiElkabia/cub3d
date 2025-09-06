/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:03:10 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/06 12:00:02 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	skip_identifier(char *line, int id)
{
	int		i;
	char	*type;

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

void	validate_texture_path(char *path, t_game *game)
{
	int	len;
	int	fd;

	if (!path)
		error_and_cleanup("Error: Empty texture path", game);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		error_and_cleanup("Error: Texture must be .xpm file", game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_and_cleanup("Error: Cannot open texture file", game);
	close(fd);
}

void	parse_texture(char *line, t_game *game, int id)
{
	int	i;
	int	path_start;

	if (game->texture[id].path)
		error_and_cleanup("Texture defined more than once", game);
	i = skip_identifier(line, id);
	if (i == -1)
		error_and_cleanup("Invalid texture line", game);
	path_start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	game->texture[id].path = ft_substr(line, path_start, i - path_start);
	if (!game->texture[id].path)
		error_and_cleanup("Malloc failed in parse_texture", game);
	validate_texture_path(game->texture[id].path, game);
}
