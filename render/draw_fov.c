#include "../includes/cub3d.h"

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	double dx = x1 - x0;
	double dy = y1 - y0;
	double steps;
	double x_inc;
	double y_inc;
	double x = x0;
	double y = y0;

	steps = fmax(fabs(dx), fabs(dy));

	if (steps == 0)
		return;

	x_inc = game->player.pos.x;
	y_inc = game->player.pos.y;
	while (steps > 0)
	{
		int map_y = (game->player.pos.y - (int)game->player.pos.y);
		int map_x = (game->player.pos.x - (int)game->player.pos.x);
		if (map_y >= 0 && map_y < game->map.height &&
			map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]) &&
			game->map.grid[map_y][map_x] != '1')
			my_mlx_pixel_put(&game->img, (int)x, (int)y, color);
		else
			break;
		x += x_inc;
		y += y_inc;
		map_x++;
		map_y++;
		steps--;
	}
}

// void	draw_fov(t_game *game)
// {
// 	double scale = 150;
// 	int px = game->player.pos.x * MINI_MAP;
// 	int py = game->player.pos.y * MINI_MAP;
// 	int dx;
// 	int dy;

// 	dx = game->player.dir.x * scale;
// 	dy = game->player.dir.y * scale;
// 	draw_line(game, px, py, px + dx, py + dy,  0x00FF00);
// }

void draw_fov(t_game *game)
{
	double scale = 50;
	// int px = game->player.pos.x * MINI_MAP;
	// int py = game->player.pos.y * MINI_MAP;
	double center_tile_x = MINI_VIEW_W / 2;
    double center_tile_y = MINI_VIEW_H / 2;

    int px = (center_tile_x * MINI_TILE) 
             + (game->player.pos.x - (int)game->player.pos.x) * MINI_TILE;
    int py = (center_tile_y * MINI_TILE) 
             + (game->player.pos.y - (int)game->player.pos.y) * MINI_TILE;
	// double player_angle = atan2(game->player.dir.y, game->player.dir.x);
	// double start_angle = player_angle - FOV_ANGLE / 2.0;
	// double angle_step = FOV_ANGLE / 20.0; // 20 rays across FOV
	// int i;
	int dx = game->player.dir.x * scale;
	int dy = game->player.dir.y * scale;
	draw_line(game, px, py, px + dx, py + dy,  0x00FF00);

	// Draw multiple rays across the FOV
	// i = 0;
	// while (i <= 20)
	// {
	// 	double current_angle = start_angle + (i * angle_step);
	// 	double dx = cos(current_angle) * scale;
	// 	double dy = sin(current_angle) * scale;

	// 	draw_line(game, px, py, px + dx, py + dy, 0x00FF00);
	// 	i++;
	// }
}