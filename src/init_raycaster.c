/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:32:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:32:18 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_horz_data(t_mlx_data *data, double *ray_angle, t_raycast *vars)
{
	vars->is_ray_facing_down = (*ray_angle > 0 && *ray_angle < PI);
	vars->is_ray_facing_up = !vars->is_ray_facing_down;
	vars->is_ray_facing_right = (*ray_angle < 0.5 * PI
			|| *ray_angle > 1.5 * PI);
	vars->is_ray_facing_left = !vars->is_ray_facing_right;
	vars->found_horz_wall_hit = false;
	vars->horz_wall_hit_x = 0;
	vars->horz_wall_hit_y = 0;
	vars->horz_wall_content = 0;
	vars->yintercept = floor(data->player.y / data->tile_size)
		* data->tile_size;
	if (vars->is_ray_facing_down)
		vars->yintercept += data->tile_size;
	vars->xintercept = data->player.x
		+ (vars->yintercept - data->player.y) / tan(*ray_angle);
	vars->ystep = data->tile_size;
	if (vars->is_ray_facing_up)
		vars->ystep *= -1;
	vars->xstep = data->tile_size / tan(*ray_angle);
	if (vars->is_ray_facing_left && vars->xstep > 0)
		vars->xstep *= -1;
	if (vars->is_ray_facing_right && vars->xstep < 0)
		vars->xstep *= -1;
	vars->next_horz_touch_x = vars->xintercept;
	vars->next_horz_touch_y = vars->yintercept;
}

void	init_ver_data(t_mlx_data *data, t_raycast *vars, double *ray_angle)
{
	vars->found_ver_wall_hit = false;
	vars->ver_wall_hit_x = 0;
	vars->ver_wall_hit_y = 0;
	vars->ver_wall_content = 0;
	vars->xintercept = floor(data->player.x / data->tile_size)
		* data->tile_size;
	if (vars->is_ray_facing_right)
		vars->xintercept += data->tile_size;
	vars->yintercept = data->player.y
		+ (vars->xintercept - data->player.x) * tan(*ray_angle);
	vars->xstep = data->tile_size;
	if (vars->is_ray_facing_left)
		vars->xstep *= -1;
	vars->ystep = data->tile_size * tan(*ray_angle);
	if (vars->is_ray_facing_up && vars->ystep > 0)
		vars->ystep *= -1;
	if (vars->is_ray_facing_down && vars->ystep < 0)
		vars->ystep *= -1;
	vars->next_ver_touch_x = vars->xintercept;
	vars->next_ver_touch_y = vars->yintercept;
}

void	init_numbers(t_mlx_data *data, t_numb_u *number_util, int i)
{
	number_util->prep_distance = data->rays[i].distance
		* cos(data->rays[i].ray_angle - data->player.rotation_angle);
	number_util->distance_proj_plan = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	number_util->projected_wall_height = (data->tile_size
			/ number_util->prep_distance) * number_util->distance_proj_plan;
	number_util->wall_strip_height = (int)number_util->projected_wall_height;
	number_util->wall_top_pixel = (WINDOW_HEIGHT / 2)
		- (number_util->wall_strip_height / 2);
	if (number_util->wall_top_pixel < 0)
		number_util->wall_top_pixel = 0;
	number_util->wall_bottom_pixel = (WINDOW_HEIGHT / 2)
		+ (number_util->wall_strip_height / 2);
	if (number_util->wall_bottom_pixel > WINDOW_HEIGHT)
		number_util->wall_bottom_pixel = WINDOW_HEIGHT;
	if (data->rays[i].was_hit_vertical)
		number_util->ofsetx = (int)data->rays[i].wall_hit_y % data->tile_size;
	else
		number_util->ofsetx = (int)data->rays[i].wall_hit_x % data->tile_size;
}

void	init_textures(t_dir_img *d_t, t_mlx_data data)
{
	d_t->north.img = mlx_xpm_file_to_image(data.mlx_ptr,
			data.map_data.north_texture, &d_t->north.x, &d_t->north.y);
	d_t->south.img = mlx_xpm_file_to_image(data.mlx_ptr,
			data.map_data.south_texture, &d_t->south.x, &d_t->south.y);
	d_t->east.img = mlx_xpm_file_to_image(data.mlx_ptr,
			data.map_data.east_texture, &d_t->east.x, &d_t->east.y);
	d_t->west.img = mlx_xpm_file_to_image(data.mlx_ptr,
			data.map_data.west_textrure, &d_t->west.x, &d_t->west.y);
	check_the_textures(*d_t);
	d_t->north.addr = mlx_get_data_addr(d_t->north.img,
			&d_t->north.bits_per_pixel,
			&d_t->north.line_size, &d_t->north.endian);
	d_t->south.addr = mlx_get_data_addr(d_t->south.img,
			&d_t->south.bits_per_pixel,
			&d_t->south.line_size, &d_t->south.endian);
	d_t->east.addr = mlx_get_data_addr(d_t->east.img,
			&d_t->east.bits_per_pixel,
			&d_t->east.line_size, &d_t->east.endian);
	d_t->west.addr = mlx_get_data_addr(d_t->west.img,
			&d_t->west.bits_per_pixel,
			&d_t->west.line_size, &d_t->west.endian);
}
