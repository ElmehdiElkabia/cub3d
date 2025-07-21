#include "../includes/cub3d.h"

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	double	dx = x1 - x0;
	double	dy = y1 - y0;
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x = x0;
	double	y = y0;

	steps = fmax(fabs(dx), fabs(dy));

	if (steps == 0)
		return ;

	x_inc = dx / steps;
	y_inc = dy / steps;
	while (steps > 0)
	{
		int map_y = (int)y / TILE_SIZE;
		int map_x = (int)x / TILE_SIZE;
		if (map_y >= 0 && map_y < game->map.height &&
			map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]) &&
			game->map.grid[map_y][map_x] != '1')
			my_mlx_pixel_put(&game->img, (int)x, (int)y, color);
		else
			break ;
		x += x_inc;
		y += y_inc;
		map_x++;
		map_y++;
		steps--;
	}
}

void	draw_fov(t_game *game)
{
	double scale = 150;
	int px = game->player.pos.x * TILE_SIZE;
	int py = game->player.pos.y * TILE_SIZE;
	int dx;
	int dy;

	dx = game->player.dir.x * scale;
	dy = game->player.dir.y * scale;
	draw_line(game, px, py, px + dx, py + dy,  0x00FF00);
}
