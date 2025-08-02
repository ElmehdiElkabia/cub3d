/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:54:53 by eelkabia          #+#    #+#             */
/*   Updated: 2025/07/26 16:37:21 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "mlx/mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IMAGE_WIDTH 1280
#define IMAGE_HIEGHT 720
#define TILE_SIZE 64
#define MINI_MAP 64
#define M_PI 3.14159265358979323846
#define FOV_ANGLE (60 * (M_PI / 180))

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
	char **map_lines;
	int map_line_count;
	int in_map;
} t_game;

void *parser_file(char *file, t_game *game);
void parse_texture(char *line, t_game *game, int id);
void parse_colors(char *line, t_game *game, int id);
void parse_map(char *line, t_game *game);
int is_map_line(char *line);
int print_error(char *str);
void ft_free_split(char **arr);
void check_map(t_game *game);
void check_characters(t_game *game);
void check_player(t_game *game);
void check_closure(t_game *game);

void init_game(t_game *data);
void init_minilibx(t_game *data);

void print_map(char **grid);

void load_textures(t_game *game);
int render_frame(t_game *data);
void raycasting(t_game *data);
void set_player_direction(t_game *game);

void drawing_map(t_game *data);
void draw_fov(t_game *game);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int update_player(int keycode, t_game *game);

void flood_fill(char **map, int x, int y);
void find_player_position(char **map, int *px, int *py);
char **duplicate_map(char **original);
#endif