#include "../includes/cub3d.h"

int mouse(int x, int y, t_game *game)
{
    static int last_x = -1;
    int dx;
    (void)y;
    if (last_x == -1)
        last_x = x;

    dx = x - last_x;
    last_x = x;

    double rot = dx * game->player.rot_speed * 0.04;

    // rotate right if dx positive, left if negative
    double old_dir_x = game->player.dir.x;
    game->player.dir.x = game->player.dir.x * cos(rot) - game->player.dir.y * sin(rot);
    game->player.dir.y = old_dir_x * sin(rot) + game->player.dir.y * cos(rot);

    double old_plane_x = game->player.plane.x;
    game->player.plane.x = game->player.plane.x * cos(rot) - game->player.plane.y * sin(rot);
    game->player.plane.y = old_plane_x * sin(rot) + game->player.plane.y * cos(rot);

    return 0;
}