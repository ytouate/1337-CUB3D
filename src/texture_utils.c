/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:34:27 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:34:28 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_the_textures(t_dir_img d_t)
{
	if (d_t.east.img == NULL || d_t.north.img == NULL)
		ft_error(UNEXPECTED_FLOW, "WRONG TEXTURE PATH\n");
	if (d_t.west.img == NULL || d_t.south.img == NULL)
		ft_error(UNEXPECTED_FLOW, "WRONG TEXTURE PATH\n");
}

void	hit_vertical(t_mlx_data *data, int i, t_numb_u number_util
						, t_dir_img d_t)
{
	if (data->rays[i].was_hit_vertical && data->rays[i].is_ray_facing_left)
	{
		number_util.ofsety = number_util.distance * ((float)d_t.west.y
				/ number_util.wall_strip_height);
		number_util.e = *(int *)(d_t.west.addr + d_t.west.line_size
				* number_util.ofsety + number_util.ofsetx
				* (d_t.west.bits_per_pixel / 8));
		*(int *)number_util.dst = number_util.e;
	}
	else if (data->rays[i].is_ray_facing_right
		&& data->rays[i].was_hit_vertical)
	{
		number_util.ofsety = number_util.distance
			* ((float)d_t.east.y / number_util.wall_strip_height);
		number_util.e = *(int *)(d_t.east.addr + d_t.east.line_size
				* number_util.ofsety + number_util.ofsetx
				* (d_t.east.bits_per_pixel / 8));
		*(int *)number_util.dst = number_util.e;
	}
}

void	hit_horizontal(t_mlx_data *data, int i,
	t_numb_u number_util, t_dir_img d_t)
{
	if (!(data->rays[i].was_hit_vertical) && data->rays[i].is_ray_facing_up)
	{
		number_util.ofsety = number_util.distance
			* ((float)d_t.north.y / number_util.wall_strip_height);
		number_util.e = *(int *)(d_t.north.addr + d_t.north.line_size
				* number_util.ofsety + number_util.ofsetx
				* (d_t.north.bits_per_pixel / 8));
		*(int *)number_util.dst = number_util.e;
	}
	else
	{
		number_util.ofsety = number_util.distance
			* ((float)d_t.south.y / number_util.wall_strip_height);
		number_util.e = *(int *)(d_t.south.addr + d_t.south.line_size
				* number_util.ofsety + number_util.ofsetx
				* (d_t.south.bits_per_pixel / 8));
		*(int *)number_util.dst = number_util.e;
	}
}

void	render_3d(t_mlx_data *data)
{
	t_dir_img	d_t;
	t_numb_u	number_util;
	int			i;
	int			j;

	i = -1;
	init_textures(&d_t, *data);
	while (++i < WINDOW_WIDTH)
	{
		init_numbers(data, &number_util, i);
		j = number_util.wall_top_pixel - 1;
		while (++j < number_util.wall_bottom_pixel)
		{
			number_util.distance = j + (number_util.wall_strip_height / 2)
				- (WINDOW_HEIGHT / 2);
			number_util.dst = data->main_img.addr;
			number_util.dst += (j * data->main_img.line_size
					+ i * (data->main_img.bits_per_pixel / 8));
			if (data->rays[i].was_hit_vertical)
				hit_vertical(data, i, number_util, d_t);
			else
				hit_horizontal(data, i, number_util, d_t);
		}
	}
}
