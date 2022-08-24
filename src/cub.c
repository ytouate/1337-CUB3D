/*                                                                            */
/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/12 12:33:30 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

float	get_player_dir(char c)
{
	if (c == 'N')
		return (N);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
	else if (c == 'S')
		return (S);
	return (0);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
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

void	rotate_player(t_mlx_data *data)
{
	data->player.rotation_angle += data->player.turn_direction * TURN_SPEED;
	update(data);
	ft_render(data);
}

int		map_has_wall_at(t_mlx_data *data, float x, float y)
{
	int	x_index;
	int	y_index;

	if (x < 0 || x > data->window_width || y < 0 || y > data->window_height)
		return (true);
	x_index = floor(x / data->tile_size);
	y_index = floor(y / data->tile_size);
	if (y_index < 0 || y_index >= data->map_data.map_lines)
		return (true);
	if (data->map_data.map[y_index]
		&& (x_index < 0
			|| x_index > (int)ft_strlen(data->map_data.map[y_index])))
		return (true);
	return (data->map_data.map[y_index][x_index] != '0'
		&& !ft_isalpha(data->map_data.map[y_index][x_index]));
}

void	move_player(t_mlx_data *data)
{
	float	new_x;
	float	new_y;
	float	move_step;

	move_step = data->player.walk_direction * MOVE_STEP;
	new_x = data->player.x + cos(data->player.rotation_angle) * move_step;
	new_y = data->player.y + sin(data->player.rotation_angle) * move_step;
	if (!map_has_wall_at(data, new_x, new_y))
	{
		update(data);
		data->player.x = new_x;
		data->player.y = new_y;
	}
	ft_render(data);
}

int	process_input(int keycode, t_mlx_data *data) {
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == UP)
		data->player.walk_direction = 1;
	else if (keycode == BOTTOM)
		data->player.walk_direction = -1;
	else if (keycode == A_KEY)
		data->player.turn_direction = -1;
	else if (keycode == D_KEY)
		data->player.turn_direction = 1;
	return (0);
}

void	setup(t_mlx_data *data)
{
	get_player_pos(data);
	data->window_height = data->map_data.map_lines * data->tile_size;
	data->window_width = data->map_data.longest_line * data->tile_size;
	data->rays = malloc(sizeof(t_rays) * WINDOW_WIDTH);
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
}

void	render_player(t_mlx_data *data)
{
	ddaline (
		SCALE * data->player.x,
		SCALE * data->player.y,
		SCALE * (data->player.x + cos(data->player.rotation_angle) * 40),
		SCALE * (data->player.y + sin(data->player.rotation_angle) * 40),
		data,
		MINI_MAP,
		0xFF0000
		);
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(t_mlx_data *data, float ray_angle, int stripId)
{
	t_raycast	vars;

	ray_angle = normalize_angle(ray_angle);
	vars.is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	vars.is_ray_facing_up = !vars.is_ray_facing_down;
	vars.is_ray_facing_right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	vars.is_ray_facing_left = !vars.is_ray_facing_right;
	vars.found_horz_wall_hit = false;
	vars.horz_wall_hit_x = 0;
	vars.horz_wall_hit_y = 0;
	vars.horz_wall_content = 0;
	vars.yintercept = floor(data->player.y / data->tile_size) * data->tile_size;
	if (vars.is_ray_facing_down)
		vars.yintercept += data->tile_size;
	vars.xintercept = data->player.x
		+ (vars.yintercept - data->player.y) / tan(ray_angle);
	vars.ystep = data->tile_size;
	if (vars.is_ray_facing_up)
		vars.ystep *= -1;
	vars.xstep = data->tile_size / tan(ray_angle);
	if (vars.is_ray_facing_left && vars.xstep > 0)
		vars.xstep *= -1;
	if (vars.is_ray_facing_right && vars.xstep < 0)
		vars.xstep *= -1;
	vars.next_horz_touch_x = vars.xintercept;
	vars.next_horz_touch_y = vars.yintercept;
	while (vars.next_horz_touch_x >= 0
		&& vars.next_horz_touch_x <= data->window_width
		&& vars.next_horz_touch_y >= 0
		&& vars.next_horz_touch_y <= data->window_height)
	{
		vars.x_to_check = vars.next_horz_touch_x;
		vars.y_to_check = vars.next_horz_touch_y;
		if (vars.is_ray_facing_up)
			vars.y_to_check += -1;
		vars.flag = 0;
		if (map_has_wall_at(data, vars.x_to_check, vars.y_to_check))
		{
			vars.horz_wall_hit_x = vars.next_horz_touch_x;
			vars.horz_wall_hit_y = vars.next_horz_touch_y;
			vars.temp_x = floor(vars.y_to_check / data->tile_size);
			vars.temp_y = floor(vars.x_to_check / data->tile_size);
			if (vars.temp_y >= data->map_data.map_lines || vars.temp_y < 0)
				vars.flag = 1;
			else if (vars.temp_x < 0
				|| vars.temp_x
				> (int)ft_strlen(data->map_data.map[vars.temp_y]))
				vars.flag = 1;
			if (vars.flag)
			{
				vars.horz_wall_content = '1';
				vars.found_horz_wall_hit = true;
			}
			else
			{
				vars.horz_wall_content
					= data->map_data.map[vars.temp_y][vars.temp_x];
				vars.found_horz_wall_hit = true;
			}
			break ;
		}
		else
		{
			vars.next_horz_touch_x += vars.xstep;
			vars.next_horz_touch_y += vars.ystep;
		}
	}
	vars.found_ver_wall_hit = false;
	vars.ver_wall_hit_x = 0;
	vars.ver_wall_hit_y = 0;
	vars.ver_wall_content = 0;
	vars.xintercept = floor(data->player.x / data->tile_size) * data->tile_size;
	if (vars.is_ray_facing_right)
		vars.xintercept += data->tile_size;
	vars.yintercept = data->player.y
		+ (vars.xintercept - data->player.x) * tan(ray_angle);
	vars.xstep = data->tile_size;
	if (vars.is_ray_facing_left)
		vars.xstep *= -1;
	vars.ystep = data->tile_size * tan(ray_angle);
	if (vars.is_ray_facing_up && vars.ystep > 0)
		vars.ystep *= -1;
	if (vars.is_ray_facing_down && vars.ystep < 0)
		vars.ystep *= -1;
	vars.next_ver_touch_x = vars.xintercept;
	vars.next_ver_touch_y = vars.yintercept;
	while (vars.next_ver_touch_x >= 0
		&& vars.next_ver_touch_x <= data->window_width
		&& vars.next_ver_touch_y >= 0
		&& vars.next_ver_touch_y <= data->window_height)
	{
		vars.x_to_check = vars.next_ver_touch_x;
		if (vars.is_ray_facing_left)
			vars.x_to_check += -1;
		vars.y_to_check = vars.next_ver_touch_y;
		if (map_has_wall_at(data, vars.x_to_check, vars.y_to_check))
		{
			vars.flag = 0;
			vars.ver_wall_hit_x = vars.next_ver_touch_x;
			vars.ver_wall_hit_y = vars.next_ver_touch_y;
			vars.temp_x = floor(vars.y_to_check / data->tile_size);
			vars.temp_y = floor(vars.x_to_check / data->tile_size);
			if (vars.temp_y >= data->map_data.map_lines || vars.temp_y < 0)
				vars.flag = 1;
			else if (vars.temp_x < 0
				|| vars.temp_x
				> (int)ft_strlen(data->map_data.map[vars.temp_y]))
				vars.flag = 1;
			if (vars.flag)
			{
				vars.ver_wall_content = '1';
				vars.found_ver_wall_hit = true;
			}
			else
			{
				vars.ver_wall_content
					= data->map_data.map[vars.temp_y][vars.temp_x];
				vars.found_ver_wall_hit = true;
			}
			break ;
		}
		else
		{
			vars.next_ver_touch_x += vars.xstep;
			vars.next_ver_touch_y += vars.ystep;
		}
	}
	if (vars.found_horz_wall_hit)
		vars.horz_hit_distance = distance_between_points(data->player.x,
				data->player.y,
				vars.horz_wall_hit_x,
				vars.horz_wall_hit_y);
	else
		vars.horz_hit_distance = FLT_MAX;
	if (vars.found_ver_wall_hit)
		vars.ver_hit_distance = distance_between_points(data->player.x,
				data->player.y,
				vars.ver_wall_hit_x,
				vars.ver_wall_hit_y);
	else
		vars.ver_hit_distance = FLT_MAX;
	if (vars.ver_hit_distance < vars.horz_hit_distance)
	{
		data->rays[stripId].distance = vars.ver_hit_distance;
		data->rays[stripId].wall_hit_x = vars.ver_wall_hit_x;
		data->rays[stripId].wall_hit_y = vars.ver_wall_hit_y;
		data->rays[stripId].wall_hit_content = vars.ver_wall_content;
		data->rays[stripId].was_hit_vertical = true;
	}
	else
	{
		data->rays[stripId].distance = vars.horz_hit_distance;
		data->rays[stripId].wall_hit_x = vars.horz_wall_hit_x;
		data->rays[stripId].wall_hit_y = vars.horz_wall_hit_y;
		data->rays[stripId].wall_hit_content = vars.horz_wall_content;
		data->rays[stripId].was_hit_vertical = false;
	}
	data->rays[stripId].ray_angle = ray_angle;
	data->rays[stripId].is_ray_facing_down = vars.is_ray_facing_down;
	data->rays[stripId].is_ray_facing_up = vars.is_ray_facing_up;
	data->rays[stripId].is_ray_facing_left = vars.is_ray_facing_left;
	data->rays[stripId].is_ray_facing_right = vars.is_ray_facing_right;
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

void	check_the_textures(t_dir_img d_t)
{
	if (d_t.east.img == NULL || d_t.north.img == NULL)
		ft_error(UNEXPECTED_FLOW, "wrong path!!");
	if (d_t.west.img == NULL || d_t.south.img == NULL)
		ft_error(UNEXPECTED_FLOW, "wrong path!!");
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

void	hit_vertical(t_mlx_data *data, int i, t_numb_u number_util
						, t_dir_img d_t)
{
	if (data->rays[i].was_hit_vertical && data->rays[i].is_ray_facing_left)
	{
		number_util.ofsety = number_util.distance * ((float)d_t.west.y
				/ number_util.wall_strip_height);
		number_util.e = *(int *)(d_t.west.addr + d_t.west.line_size *
				number_util.ofsety + number_util.ofsetx
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

void	generate_3d_projection(t_mlx_data *data)
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

bool	is_there_a_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

void	get_player_pos(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map_data.map[i])
	{
		j = 0;
		while (data->map_data.map[i][j])
		{
			if (is_there_a_player(data->map_data.map[i][j]))
			{
				data->player.x = j * data->tile_size + 1;
				data->player.y = i * data->tile_size + 1;
				data->map_data.map[i][j] = '0';
				data->player.rotation_angle
					= get_player_dir(data->map_data.map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	reset(int keycode, t_mlx_data *data)
{
	if (keycode == UP)
		data->player.walk_direction = 0;
	else if (keycode == BOTTOM)
		data->player.walk_direction = 0;
	else if (keycode == A_KEY)
		data->player.turn_direction = 0;
	else if (keycode == D_KEY)
		data->player.turn_direction = 0;
	return (0);
}

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
	data->map_img.img = mlx_new_image(
			data->mlx_ptr,
			data->window_width * SCALE,
			data->window_height * SCALE
			);
	data->map_img.addr = mlx_get_data_addr(
			data->map_img.img,
			&data->map_img.bits_per_pixel,
			&data->map_img.line_size,
			&data->map_img.endian
			);
}

void	map_setup(t_mlx_data *data)
{
	fill_map(data);
	check_all_the_map(&data->map_data);
}

int	handle_keys(t_mlx_data *data)
{
	if (data->player.walk_direction == 1 || data->player.walk_direction == -1)
		move_player(data);
	if (data->player.turn_direction == 1 || data->player.turn_direction == -1)
		rotate_player(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data.tile_size = 64;
	check_basic_requirements(ac, av);
	data.map_data.map_name = av[1];
	map_setup(&data);
	setup(&data);
	init_window(&data);
	ft_render(&data);
	mlx_hook(data.window, 17, 0, ft_close, &data);
	mlx_hook(data.window, KEYPRESS, KEYPRESSMASK, process_input, &data);
	mlx_hook(data.window, KEYRELEASE, KEYRELEASEMASK, reset, &data);
	mlx_loop_hook(data.mlx_ptr, handle_keys, &data);
	mlx_loop(data.mlx_ptr);
}
