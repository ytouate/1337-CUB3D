/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collosions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:40:10 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:40:12 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_has_wall_at(t_mlx_data *data, float x, float y)
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
