/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:33:56 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/04 15:10:25 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	error_and_cleanup(char *str, t_game *game)
{
	printf("%s\n", str);
	if (game)
	{
		if (game->current_line)
		{
			free(game->current_line);
			game->current_line = NULL;
		}
		get_next_line(-1);
		free_map_data(game);
		free_texture_data(game);
	}
	exit(1);
}

void	free_doors(t_game *game)
{
	if (game->map.doors)
	{
		free(game->map.doors);
		game->map.doors = NULL;
	}
	game->map.door_count = 0;
}
