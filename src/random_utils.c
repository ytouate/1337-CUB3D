/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:35:49 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 14:35:50 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	is_there_a_player(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

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
