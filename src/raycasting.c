/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:31:27 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:31:42 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	horz_intercetion(t_mlx_data *data, t_raycast *vars)
{
	while (vars->next_horz_touch_x >= 0
		&& vars->next_horz_touch_x <= data->window_width
		&& vars->next_horz_touch_y >= 0
		&& vars->next_horz_touch_y <= data->window_height)
	{
		vars->x_to_check = vars->next_horz_touch_x;
		vars->y_to_check = vars->next_horz_touch_y;
		if (vars->is_ray_facing_up)
			vars->y_to_check += -1;
		vars->flag = 0;
		if (map_has_wall_at(data, vars->x_to_check, vars->y_to_check))
		{
			get_horz_ray_data(data, vars);
			break ;
		}
		else
		{
			vars->next_horz_touch_x += vars->xstep;
			vars->next_horz_touch_y += vars->ystep;
		}
	}
}

void	ver_intersection(t_mlx_data *data, t_raycast *vars)
{
	while (vars->next_ver_touch_x >= 0
		&& vars->next_ver_touch_x <= data->window_width
		&& vars->next_ver_touch_y >= 0
		&& vars->next_ver_touch_y <= data->window_height)
	{
		vars->x_to_check = vars->next_ver_touch_x;
		if (vars->is_ray_facing_left)
			vars->x_to_check += -1;
		vars->y_to_check = vars->next_ver_touch_y;
		if (map_has_wall_at(data, vars->x_to_check, vars->y_to_check))
		{
			get_ver_ray_data(data, vars);
			break ;
		}
		else
		{
			vars->next_ver_touch_x += vars->xstep;
			vars->next_ver_touch_y += vars->ystep;
		}
	}
}

void	get_closest_wall_hit(t_mlx_data *data, t_raycast *vars)
{
	if (vars->found_horz_wall_hit)
		vars->horz_hit_distance = distance_between_points(data->player.x,
				data->player.y,
				vars->horz_wall_hit_x,
				vars->horz_wall_hit_y);
	else
		vars->horz_hit_distance = FLT_MAX;
	if (vars->found_ver_wall_hit)
		vars->ver_hit_distance = distance_between_points(data->player.x,
				data->player.y,
				vars->ver_wall_hit_x,
				vars->ver_wall_hit_y);
	else
		vars->ver_hit_distance = FLT_MAX;
}

void	cast_ray(t_mlx_data *data, double ray_angle, int column)
{
	t_raycast	vars;

	ray_angle = normalize_angle(ray_angle);
	init_horz_data(data, &ray_angle, &vars);
	horz_intercetion(data, &vars);
	init_ver_data(data, &vars, &ray_angle);
	ver_intersection(data, &vars);
	get_closest_wall_hit(data, &vars);
	fill_ray_data(data, &vars, column, ray_angle);
}

void	cast_all_rays(t_mlx_data *data)
{
	float	ray_angle;
	int		strip_id;

	strip_id = 0;
	ray_angle = data->player.rotation_angle - (FOV / 2);
	while (strip_id < WINDOW_WIDTH)
	{
		cast_ray(data, ray_angle, strip_id);
		ray_angle += (FOV / WINDOW_WIDTH);
		strip_id++;
	}
}
