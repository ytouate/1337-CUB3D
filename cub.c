/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/27 12:35:02 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"



int	hook_into_key_events(int keycode, t_mlx_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->window);
		TODO:
		// TODO:
			// Free all the resources;
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	// free resources;
	exit(EXIT_SUCCESS);
	return(0);
}

int	check_file_extention(char *file)
{
	int last;
	int len;

	len = ft_strlen(file);
	last = len - 1;

	if (len > 4)
		return (file[last] == 'b' && file[last - 1] == 'u' && file[last - 2] == 'c' && file[last - 3] == '.');
	return (false);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();
	data.window_x_size = 600;
	data.window_y_size = 350;
	if (ac < 2)
		ft_error(1, "Not Enough Arguments\n");
	if (!check_file_extention(av[1]))
		ft_error(1, "Check the file extention\n");
	data.window = mlx_new_window(data.mlx_ptr, data.window_x_size, data.window_y_size, "Cub3D");
	// mlx_hook(data.window, 17, 0, ft_close, &data); 
	mlx_key_hook(data.window, hook_into_key_events, &data);
	mlx_loop(data.mlx_ptr);
}
