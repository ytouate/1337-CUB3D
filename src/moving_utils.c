/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:25:44 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:25:46 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	rotate_player(t_mlx_data *data)
{
	data->player.rotation_angle += data->player.turn_direction * TURN_SPEED;
	update(data);
	ft_render(data);
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