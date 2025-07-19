#include "includes/cub3d.h"

//hadchy ba9i khdam alih mat9isoch !! 
// void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

// void    draw_square(t_game *data, int y, int x, int color)
// {
    
// }
// void    draw_cercle()
// {

// }
// void    drawing_map(t_game *data)
// {
//     int y;
//     int x;
//     y = 0;

//     while (y < data->map.height)
//     {
//         x = 0;
//         while (x < ft_strlen(data->map.grid[y]))
//         {
//             if(data->map.grid[y][x] == '1')
//                 draw_square();
//             else if(data->map.grid[y][x] == '0')
//                 draw_square();
//             else if(data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'W' || data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'S')
//                 draw_cercle();
//             else if(data->map.grid[y][x] == ' ')
//                 draw_square();
//             x++;
//         }
//         y++;
//     }
//     return ;
// }