/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:33:56 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/19 13:03:09 by eelkabia         ###   ########.fr       */
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
		free_map_data(game);
		free_texture_data(game);
	}
	exit(1);
}
