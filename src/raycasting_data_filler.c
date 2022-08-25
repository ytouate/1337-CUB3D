/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_data_filler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:37:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:37:57 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_ver_ray_data(t_mlx_data *data, t_raycast *vars)
{
	vars->flag = 0;
	vars->ver_wall_hit_x = vars->next_ver_touch_x;
	vars->ver_wall_hit_y = vars->next_ver_touch_y;
	vars->temp_x = floor(vars->y_to_check / data->tile_size);
	vars->temp_y = floor(vars->x_to_check / data->tile_size);
	if (vars->temp_y >= data->map_data.map_lines || vars->temp_y < 0)
		vars->flag = 1;
	else if (vars->temp_x < 0
		|| vars->temp_x
		> (int)ft_strlen(data->map_data.map[vars->temp_y]))
		vars->flag = 1;
	if (vars->flag)
	{
		vars->ver_wall_content = '1';
		vars->found_ver_wall_hit = true;
	}
	else
	{
		vars->ver_wall_content
			= data->map_data.map[vars->temp_y][vars->temp_x];
		vars->found_ver_wall_hit = true;
	}
}

void	get_horz_ray_data(t_mlx_data *data, t_raycast *vars)
{
	vars->horz_wall_hit_x = vars->next_horz_touch_x;
	vars->horz_wall_hit_y = vars->next_horz_touch_y;
	vars->temp_x = floor(vars->y_to_check / data->tile_size);
	vars->temp_y = floor(vars->x_to_check / data->tile_size);
	if (vars->temp_y >= data->map_data.map_lines || vars->temp_y < 0)
		vars->flag = 1;
	else if (vars->temp_x < 0
		|| vars->temp_x
		> (int)ft_strlen(data->map_data.map[vars->temp_y]))
		vars->flag = 1;
	if (vars->flag)
	{
		vars->horz_wall_content = '1';
		vars->found_horz_wall_hit = true;
	}
	else
	{
		vars->horz_wall_content
			= data->map_data.map[vars->temp_y][vars->temp_x];
		vars->found_horz_wall_hit = true;
	}	
}

void	fill_ray_data(t_mlx_data *data,
		t_raycast *vars, int column, double ray_angle)
{
	if (vars->ver_hit_distance < vars->horz_hit_distance)
	{
		data->rays[column].distance = vars->ver_hit_distance;
		data->rays[column].wall_hit_x = vars->ver_wall_hit_x;
		data->rays[column].wall_hit_y = vars->ver_wall_hit_y;
		data->rays[column].wall_hit_content = vars->ver_wall_content;
		data->rays[column].was_hit_vertical = true;
	}
	else
	{
		data->rays[column].distance = vars->horz_hit_distance;
		data->rays[column].wall_hit_x = vars->horz_wall_hit_x;
		data->rays[column].wall_hit_y = vars->horz_wall_hit_y;
		data->rays[column].wall_hit_content = vars->horz_wall_content;
		data->rays[column].was_hit_vertical = false;
	}
	data->rays[column].ray_angle = ray_angle;
	data->rays[column].is_ray_facing_down = vars->is_ray_facing_down;
	data->rays[column].is_ray_facing_up = vars->is_ray_facing_up;
	data->rays[column].is_ray_facing_left = vars->is_ray_facing_left;
	data->rays[column].is_ray_facing_right = vars->is_ray_facing_right;
}
