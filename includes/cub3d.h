/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:54:53 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/10 17:47:28 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_texture
{
	char *path;
	void *img;
	char *addr;
	int width;
	int height;
	int bpp;
	int line_len;
	int endian;
} t_texture;

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
	t_vector pos;
	t_vector dir;
	t_vector plane;
	double move_speed;
	double rot_speed;
} t_player;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_map
{
	char **grid;
	int width;
	int height;
	t_color floor;
	t_color ceiling;
} t_map;

typedef struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
} t_mlx;

typedef struct s_game
{
	t_mlx mlx;
	t_img img;
	t_map map;
	t_player player;
	t_texture texture[4];
} t_game;


void	parser_file(char *file, t_game *game);
int	print_error(char *str);
#endif