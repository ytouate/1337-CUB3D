/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:29:14 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:29:16 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	create_rgb(int r, int g, int b)
{
	return ((1 << 24) + (r << 16) + (g << 8) + b);
}

void	render_ceiling(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(
				&data->main_img, j, i,
				create_rgb(
					data->map_data.ceilling_color[0],
					data->map_data.ceilling_color[1],
					data->map_data.ceilling_color[2])
				);
			j++;
		}
		i++;
	}
}

void	render_floor(t_mlx_data *data)
{
	int	i;
	int	j;

	i = WINDOW_HEIGHT / 2;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(
				&data->main_img,
				j,
				i,
				create_rgb(
					data->map_data.floor_color[0],
					data->map_data.floor_color[1],
					data->map_data.floor_color[2])
				);
			j++;
		}
		i++;
	}
}

void	render_ceiling_and_floor(t_mlx_data *data)
{
	render_ceiling(data);
	render_floor(data);
}

int	ft_render(t_mlx_data *data)
{
	cast_all_rays(data);
	render_ceiling_and_floor(data);
	generate_3d_projection(data);
	mlx_put_image_to_window(
		data->mlx_ptr,
		data->window,
		data->main_img.img,
		0, 0);
	return (0);
}
