#include "../includes/cub3d.h"

void handel_dor(t_game *data)
{
    int y = data->player.pos.y;
    int x = data->player.pos.x;

    int front_y = y + (int)round(data->player.dir.y);
    int front_x = x + (int)round(data->player.dir.x);


    if (data->map.grid[front_y][front_x] == 'D')
		data->map.grid[front_y][front_x] = 'O';

    else if (data->map.grid[front_y][front_x] == 'O')
		data->map.grid[front_y][front_x] = 'D';
}