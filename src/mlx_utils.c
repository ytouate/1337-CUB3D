/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:43:10 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:43:12 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	update(t_mlx_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->window);
	data->main_img.img = mlx_new_image(
			data->mlx_ptr,
			WINDOW_WIDTH,
			WINDOW_HEIGHT
			);
	data->main_img.addr = mlx_get_data_addr(
			data->main_img.img,
			&data->main_img.bits_per_pixel,
			&data->main_img.line_size,
			&data->main_img.endian
			);
}

void	map_setup(t_mlx_data *data)
{
	fill_map(data);
	check_all_the_map(&data->map_data);
}

void	init_window(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	data->window = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			"Cub3D");
	data->main_img.img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH,
			WINDOW_HEIGHT);
	data->main_img.addr = mlx_get_data_addr(data->main_img.img,
			&data->main_img.bits_per_pixel,
			&data->main_img.line_size,
			&data->main_img.endian);
}
