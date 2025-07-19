#include "../includes/cub3d.h"

void	update_new_pos(int keycode, double *new_x, double *new_y, t_game *game)
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
}

int	update_player(int keycode, t_game *game)
{
	double	new_x = game->player.pos.x;
	double	new_y = game->player.pos.y;
	int map_x = (int)(new_x);
	int map_y = (int)(new_y);
	
	update_new_pos(keycode, &new_x, &new_y, game);
	if (game->map.grid[map_y][(int)(new_x + 0.3)] != '1' &&
		game->map.grid[map_y][(int)(new_x - 0.3)] != '1' &&
		game->map.grid[(int)(new_y + 0.3)][map_x] != '1' &&
		game->map.grid[(int)(new_y - 0.3)][map_x] != '1')
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
	}

	mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	drawing_map(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
							game->img.img, 0, 0);

	return (0);
}