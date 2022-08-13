/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:02:03 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 17:45:58 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_size + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void update_window(t_mlx_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->window);
	data->main_img->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->main_img->addr = mlx_get_data_addr(data->main_img->img,
	&data->main_img->bits_per_pixel, &data->main_img->line_size, &data->main_img->endian);
	data->map_img->img = mlx_new_image(data->mlx_ptr, 300, 195);
	data->map_img->addr = mlx_get_data_addr(data->map_img->img,
	&data->map_img->bits_per_pixel, &data->map_img->line_size, &data->map_img->endian);
}

void init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->window = mlx_new_window(mlx_data->mlx_ptr, WINDOW_WIDTH,
					WINDOW_HEIGHT, "Cub3D");
	mlx_data->main_img->img = mlx_new_image(mlx_data->mlx_ptr, WINDOW_WIDTH,
					WINDOW_HEIGHT);
	mlx_data->main_img->addr = mlx_get_data_addr(mlx_data->main_img->img,
				&mlx_data->main_img->bits_per_pixel, &mlx_data->main_img->line_size, &mlx_data->main_img->endian);
}