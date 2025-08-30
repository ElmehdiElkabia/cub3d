/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:54:53 by eelkabia          #+#    #+#             */
/*   Updated: 2025/08/30 11:40:05 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define IMAGE_WIDTH 1280
# define IMAGE_HEIGHT 720
# define TILE_SIZE 64
# define MINI_VIEW_W 10
# define MINI_VIEW_H 10
# define MINI_TILE 10
# define MINI_MAP 8
# define M_PI 3.14159265358979323846
# define FOV_ANGLE 1.0471975511965976
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define DOOR_CLOSED 0
# define DOOR_OPENING 1
# define DOOR_OPEN 2
# define DOOR_CLOSING 3

typedef struct s_door
{
	int			x;
	int			y;
	int			state;
	double		anim_progress;
	double		anim_speed;
}				t_door;

typedef struct s_texture
{
	char		*path;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
	t_texture	anim[4];
	int			frame;
	int			frame_counter;
	int			anim_playing;
}				t_player;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_color		floor;
	t_color		ceiling;
	t_door		*doors;
	int			door_count;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_mlx;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	step;
	t_vector	map;
	double		perp_wall_dist;
	int			hit;
	int			side;
}				t_ray;

typedef struct s_tex_draw
{
	int			x;
	int			tex_x;
	int			start;
	int			end;
	int			height;
}				t_tex_draw;

typedef struct s_tex_vars
{
	double		wall_x;
	t_texture	*texture;
	int			tex_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_tex_vars;

typedef struct s_draw_vars
{
	int			y;
	double		step;
	double		tex_pos;
	char		*pixel;
	int			color;
	int			tex_y;
}				t_draw_vars;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
	int			esc;
}				t_keys;

typedef struct s_game
{
	t_mlx		mlx;
	t_img		img;
	t_map		map;
	t_player	player;
	t_texture	texture[4];
	t_texture	door_texture;
	char		**map_lines;
	int			map_line_count;
	int			in_map;
	t_keys		keys;
}				t_game;

void			*parser_file(char *file, t_game *game);
void			parse_texture(char *line, t_game *game, int id);
void			parse_colors(char *line, t_game *game, int id);
void			parse_map(char *line, t_game *game);
int				is_map_line(char *line);
int				print_error(char *str);
void			error_and_cleanup(char *str, t_game *game);
void			ft_free_split(char **arr);
void			check_map(t_game *game);
void			check_characters(t_game *game);
void			check_player(t_game *game);
void			check_closure(t_game *game);

int				is_empty_line(char *line);

void			init_game(t_game *data);
void			init_minilibx(t_game *data);
void			destroy_img(t_game *data);
void			destroy_mlx(t_game *data);
void			free_map_data(t_game *data);
void			free_texture_data(t_game *data);
void			cleanup_and_exit(t_game *data, int exit_code);

void			print_map(char **grid);
int				get_map_width(t_game *data);
void			load_textures(t_game *game);
int				render_frame(t_game *data);
void			raycasting(t_game *data);
void			set_player_direction(t_game *game);

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				game_loop(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			handle_movement(double *new_x, double *new_y, t_game *game);
void			handle_exit(t_game *game);
int				close_window(t_game *game);

void			calculate_distance(t_ray *ray);
void			calculate_wall_dimensions(t_ray *r, int *line_height,
					int *draw_start, int *draw_end);
double			calculate_wall_position(t_game *data, t_ray *r);

void			texture_mapping(t_game *data, t_ray *r, int x);

void			flood_fill(char **map, int x, int y);
void			flood_fill_recursive(char **map, int x, int y, int *error_flag);
void			find_player_position(char **map, int *px, int *py);
char			**duplicate_map(char **original);

void			draw_color(t_game *game, t_ray *ray, int x);
void			rotate_vector(t_vector *vec, double angle);

void			handle_rotation(t_game *game);
int				handle_mouse(int x, int y, t_game *game);

void			draw_mini_map(t_game *game);
int				key_press_mouse(int button, int x, int y, void *param);
void			shouting(t_game *data);
void			draw_player_anim(t_game *game);

// Door parsing functions
void			init_doors(t_game *game);
void			free_doors(t_game *game);

// Door drawing functions
t_door			*get_door_at(t_game *game, int x, int y);
void			draw_door(t_game *data, t_ray *r, int x);
void			load_door_texture(t_game *game);
void			handel_dor(t_game *data);

#endif