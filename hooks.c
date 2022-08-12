/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:45:02 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 16:46:12 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

extern const int map[MAP_NUM_COLS][MAP_NUM_COLS];
int	hook_into_key_events(int keycode, t_mlx_data *data)
{
	if (keycode == ESC)
	{
		mlx_clear_window(data->mlx_ptr, data->window);
		mlx_destroy_image(data->mlx_ptr, data->img);
		mlx_destroy_window(data->mlx_ptr, data->window);
		exit(EXIT_SUCCESS);
	}
	else if (D_KEY == keycode)
	{
	}
	else if (W_KEY == keycode)
	{
		update_window(data);
		data->player.x += -sin(data->player.rotation_angle) * 10;
		data->player.y += cos(data->player.rotation_angle) * 10;
		render(data);
	}
	else if (A_KEY == keycode)
	{
	}
	else if (S_KEY == keycode)
	{
		update_window(data);
		data->player.x -= -sin(data->player.rotation_angle) * 10;
		data->player.y -= cos(data->player.rotation_angle) * 10;
		render(data);
	}
	return (0);
}

int		ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	// free resources;
	exit(EXIT_SUCCESS);
	return(0);
}

int rotate_player(int keycode,t_mlx_data *data)
{
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == LEFT)
	{
		data->player.rotation_angle -= 0.1;
		update_window(data);
		render(data);
	}
	else if (keycode == RIGHT)
	{
		update_window(data);;
		data->player.rotation_angle += 0.1;
		render(data);
	}
	else if (keycode == UP) 
	{
		update_window(data);
		float temp_x = data->player.x + -sin(data->player.rotation_angle) * 16;
		float temp_y = data->player.y + cos(data->player.rotation_angle) * 16;
		
		int x = temp_x / TILE_SIZE;
		int y = temp_y / TILE_SIZE;
		if (!(map[y][x] == 1))
		{
			data->player.x += -sin(data->player.rotation_angle) * 16;
			data->player.y += cos(data->player.rotation_angle) * 16;
		}
		render(data);
	}
	else if (keycode == BOTTOM)
	{
		update_window(data);
		float temp_x = data->player.x - -sin(data->player.rotation_angle) * 10;
		float temp_y = data->player.y - cos(data->player.rotation_angle) * 10;
		
		int x = temp_x / TILE_SIZE;
		int y = temp_y / TILE_SIZE;
		if (!(map[y][x] == 1))
		{
			data->player.x -= -sin(data->player.rotation_angle) * 10;
			data->player.y -= cos(data->player.rotation_angle) * 10;
		}
		render(data);
	}
	return (0);
}