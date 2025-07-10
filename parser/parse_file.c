/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:29:09 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/10 17:40:52 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parser_file(char *file, t_game *game)
{
	char	*line;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ()
}