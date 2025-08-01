#include "../includes/cub3d.h"

void update_new_pos(int keycode, double *new_x, double *new_y, t_game *game)
{
	if (keycode == 119) // W
	{
		*new_x += game->player.dir.x * game->player.move_speed;
		*new_y += game->player.dir.y * game->player.move_speed;
	}
	if (keycode == 115) // S
	{
		*new_x -= game->player.dir.x * game->player.move_speed;
		*new_y -= game->player.dir.y * game->player.move_speed;
	}
	if (keycode == 97) // A
	{
		*new_x -= game->player.plane.x * game->player.move_speed;
		*new_y -= game->player.plane.y * game->player.move_speed;
	}
	if (keycode == 100) // D
	{
		*new_x += game->player.plane.x * game->player.move_speed;
		*new_y += game->player.plane.y * game->player.move_speed;
	}
	if (keycode == 65363) // rotate right
	{
		double old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(game->player.rot_speed) - game->player.dir.y * sin(game->player.rot_speed);
		game->player.dir.y = old_dir_x * sin(game->player.rot_speed) + game->player.dir.y * cos(game->player.rot_speed);

		double old_plane_x = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(game->player.rot_speed) - game->player.plane.y * sin(game->player.rot_speed);
		game->player.plane.y = old_plane_x * sin(game->player.rot_speed) + game->player.plane.y * cos(game->player.rot_speed);
	}
	if (keycode == 65361) // rotate left
	{
		double old_dir_x = game->player.dir.x;
		game->player.dir.x = game->player.dir.x * cos(-game->player.rot_speed) - game->player.dir.y * sin(-game->player.rot_speed);
		game->player.dir.y = old_dir_x * sin(-game->player.rot_speed) + game->player.dir.y * cos(-game->player.rot_speed);

		double old_plane_x = game->player.plane.x;
		game->player.plane.x = game->player.plane.x * cos(-game->player.rot_speed) - game->player.plane.y * sin(-game->player.rot_speed);
		game->player.plane.y = old_plane_x * sin(-game->player.rot_speed) + game->player.plane.y * cos(-game->player.rot_speed);
	}
}

int update_player(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
		exit(0);
	}

	double new_x = game->player.pos.x;
	double new_y = game->player.pos.y;

	update_new_pos(keycode, &new_x, &new_y, game);

	int map_x = (int)(game->player.pos.x);
	int map_y = (int)(game->player.pos.y);

	if (game->map.grid[map_y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map.grid[(int)new_y][map_x] != '1')
		game->player.pos.y = new_y;

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	drawing_map(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr, game->img.img, 0, 0);

	return (0);
}
