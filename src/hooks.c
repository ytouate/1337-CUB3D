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

#include "../cub.h"

int	ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	exit(EXIT_SUCCESS);
	return (0);
}

int	process_input(int keycode, t_mlx_data *data)
{
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

int	mouse_hook(int button, int x, int y, t_mlx_data *data)
{
	int	mid;

	(void)y;
	if (button == 1)
	{
		mid = WINDOW_WIDTH / 2;
		if (x > 0 && x < mid)
		{
			data->player.turn_direction = -1;
			rotate_player(data);
			data->player.turn_direction = 0;
		}
		else if (x > mid && x < WINDOW_WIDTH)
		{
			data->player.turn_direction = +1;
			rotate_player(data);
			data->player.turn_direction = 0;
		}
	}
	move_player_with_mouse(button, data);
	return (0);
}

void	move_player_with_mouse(int button, t_mlx_data *data)
{
	if (button == 4)
	{
		data->player.walk_direction = -1;
		move_player(data);
		data->player.walk_direction = 0;
	}
	else if (button == 5)
	{
		data->player.walk_direction = 1;
		move_player(data);
		data->player.walk_direction = 0;
	}
}

int	handle_keys(t_mlx_data *data)
{
	if (data->player.walk_direction == 1 || data->player.walk_direction == -1)
		move_player(data);
	if (data->player.turn_direction == 1 || data->player.turn_direction == -1)
		rotate_player(data);
	return (0);
}
