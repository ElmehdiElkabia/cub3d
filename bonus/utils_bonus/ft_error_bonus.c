/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayadouay <ayadouay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:33:56 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/09 11:33:04 by ayadouay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	print_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
}

void	error_and_cleanup(char *str, t_game *game)
{
	print_error(str);
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
