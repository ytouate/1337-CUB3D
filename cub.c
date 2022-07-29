/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/29 10:09:18 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// the key handler function;
int	hook_into_key_events(int keycode, t_mlx_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		//TODO:
			// Free all the resources;
		exit(EXIT_SUCCESS);
	}
	return (0);
}

// closes the window when the red button is clicked;
int ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	// free resources;
	exit(EXIT_SUCCESS);
	return(0);
}

// checks the file name if it ends with .cub
int	check_file_extention(char *file)
{
	int last;
	int len;

	len = ft_strlen(file);
	last = len - 1;

	if (len > 4)
		return (file[last] == 'b' && file[last - 1] == 'u' &&
			file[last - 2] == 'c' && file[last - 3] == '.');
	return (false);
}

// initialize the map_data for good practices
void	map_data_consructor(t_map_data *map_data)
{
	map_data->north_texture = NULL;
	map_data->west_textrure = NULL;
	map_data->south_texture = NULL;
	map_data->east_texture = NULL;
	map_data->map_lines = -1;
	ft_memset(map_data->ceilling_color, -1, 3 * sizeof(int));
	ft_memset(map_data->floor_color, -1, 3 * sizeof(int));
}

int	main(int ac, char **av)
{
	t_mlx_data	data;
	t_map_data	map_data;
	data.mlx_ptr = mlx_init();
	data.window_x_size = 600;
	data.window_y_size = 350;
	if (ac < 2)
		ft_error(1, "Not Enough Arguments\n");
	if (!check_file_extention(av[1]))
		ft_error(1, "Check the file extention\n");
	map_data.map_lines = count_map_lines(av[1]);
	map_data.map = convert_file_to_grid(av[1], map_data.map_lines);
	for (int i = 0; map_data.map[i]; i++)
	{
		get_texture_path(map_data.map[i], &map_data);
	}
	check_map_texture(map_data);
	data.window = mlx_new_window(data.mlx_ptr, data.window_x_size, data.window_y_size, "Cub3D");
	mlx_hook(data.window, 17, 0, ft_close, &data); 
	mlx_key_hook(data.window, hook_into_key_events, &data);
	map_data_consructor(&map_data);
	mlx_loop(data.mlx_ptr);
}
