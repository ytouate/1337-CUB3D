/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:51:35 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/11 11:51:37 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init(t_mlx_data *data)
{
	map_data_constructor(&data->map_data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error(FUNCTION_FAILED, "mlx_init() FAILED \n");
	data->map_data.map_lines = count_map_lines(data->map_data.map_name);
	if (data->map_data.map_lines == 0)
		ft_error(UNEXPECTED_FLOW, "Empty Map\n");
}

void init_map_data(t_mlx_data *data)
{
	int map_content_start;
	char **temp_grid;
	int i;
	char *temp;

	i = 0;
	temp_grid = convert_file_to_grid(data);
	map_content_start = fill_map_data(temp_grid, data);
	data->map_data.map = malloc(sizeof(char *) * data->map_data.map_lines - map_content_start + 1);
	while (temp_grid[map_content_start])
	{
		temp = ft_strtrim(temp_grid[map_content_start++], "\n");
		data->map_data.map[i++] = temp;
		free(temp);
	}
	data->map_data.map[i] = temp_grid[map_content_start];
	free_grid(temp_grid);
	data->map_data.map_lines = i;
}

// initialize the map_data for good practices
void	map_data_constructor(t_map_data *map_data)
{
	map_data->north_texture = NULL;
	map_data->west_textrure = NULL;
	map_data->south_texture = NULL;
	map_data->east_texture = NULL;
	map_data->map_lines = -1;
	ft_memset(map_data->ceilling_color, -1, 3 * sizeof(int));
	ft_memset(map_data->floor_color, -1, 3 * sizeof(int));
}

