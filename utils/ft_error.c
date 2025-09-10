/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:33:56 by eelkabia          #+#    #+#             */
/*   Updated: 2025/09/10 14:52:31 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_error(char *str)
{
	ft_putendl_fd("Error". 2);
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
