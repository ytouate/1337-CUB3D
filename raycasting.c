/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:51:18 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/12 12:32:36 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

#define WIDTH 800
#define HEIGHT 520
#define HALF_WIDTH WIDTH / 2
#define HALF_HEIGHT HEIGHT / 2
#define MAP_SCALE 40
#define MAP_COLS 20
#define MAP_ROWS 13
#define MAP_RANGE (MAP_SCALE * (MAP_COLS * MAP_ROWS))
#define MAP_SPEED (MAP_SCALE / 2) / 10

const int m[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void render_map(t_mlx_data *data)
{
    int x;
    int y;
    x = y = 0;
    int row = 0;
    int col = 0;
    for (; row < MAP_ROWS; row++)
    {
        x = 0;
        col = 0;
        for (; col < MAP_COLS; col++)
        {
            if (m[row][col] == 1)
            {
                data->rays.height = MAP_SCALE;
                data->rays.width = MAP_SCALE;
                ft_drawsquare(data, x, y);   
            }
            x += MAP_SCALE;
        }
        y += MAP_SCALE;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->window, data->main_img->img, 0, 0);
}

// int move_player(int key, t_mlx_data *data){
//     if (key == ESC)
//         exit(EXIT_SUCCESS);
//     else if (key == UP)
//     {
//         data->player.x += - sin(data->player.rotation_angle);
//         data->player.y += cos(data->player.rotation_angle);
        
//     }
// }
// int main()
// {
//     t_mlx_data data;

//     data.mlx_ptr = mlx_init();
//     data.window = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "raycasting");
//     data.img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
//     data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_size, &data.endian);
//     data.player.x = MAP_SCALE + 20;
//     data.player.y = MAP_SCALE + 20;
//     data.player.rotation_angle = PI / 3;
    
//     ft_draw_player(&data);
//     render_map(&data);
//     // handle key pressing
//     mlx_hook(data.window, KEYPRESS, KEYPRESSMASK, move_player, &data);
//     mlx_loop(data.mlx_ptr);
// }