/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/30 11:02:38 by ytouate          ###   ########.fr       */
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
int		ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	// free resources;
	exit(EXIT_SUCCESS);
	return(0);
}

// checks the file name if it ends with .cub
int		check_file_extention(char *file)
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
	int	i = 0;
	map_data->north_texture = NULL;
	map_data->west_textrure = NULL;
	map_data->south_texture = NULL;
	map_data->east_texture = NULL;
	map_data->map_lines = -1;
	ft_memset(map_data->ceilling_color, -1, 3 * sizeof(int));
	ft_memset(map_data->floor_color, -1, 3 * sizeof(int));
}

bool is_valid_line(char *line)
{
	int i;
	i = 0;
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != ' ' && line[i] != '\t' )
			return (true);
		i++;
	}
	return (false);
}

void skip_empty_lines(char **grid, int *n)
{
	while (grid[*n])
	{
		if (is_valid_line(grid[*n]))
			return;
		*n += 1;
	}
}

void	free_grid(char **grid)
{
	int i;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;
	t_map_data	map_data;

	char	**temp_grid;
	data.mlx_ptr = mlx_init();
	data.window_x_size = 600;
	data.window_y_size = 350;
	if (ac < 2)
		ft_error(1, "A Map file-name is required !\n");
	if (!check_file_extention(av[1]))
		ft_error(1, "the file extention is not .cub\n");
	map_data.map_lines = count_map_lines(av[1]);
	temp_grid = convert_file_to_grid(av[1], map_data.map_lines);
	int flag;
	int	i;
	for (i = 0; temp_grid[i]; i++)
	{
		if (get_texture_path(temp_grid[i], &map_data))
			flag += 1;
		if (flag == 6)
			break;
	}
	int start = i + 1;
	skip_empty_lines(temp_grid, &start);
	int	end = map_data.map_lines - start;
	map_data.map = malloc(sizeof(char *) * end + 2);
	if (!map_data.map)
		ft_error(1, "Malloc Failed\n");
	i = 0;
	while (temp_grid[start])
		map_data.map[i++] = ft_strdup(temp_grid[start++]);

	map_data.map[i] = temp_grid[start];
	i = 0;
	free_grid(temp_grid);
	while (map_data.map[i])
	{
		printf("%s", map_data.map[i]);
		i++;
	}
	check_map_texture(map_data);
	data.window = mlx_new_window(data.mlx_ptr, data.window_x_size, data.window_y_size, "Cub3D");
	mlx_hook(data.window, 17, 0, ft_close, &data); 
	mlx_key_hook(data.window, hook_into_key_events, &data);
	map_data_consructor(&map_data);
	mlx_loop(data.mlx_ptr);
}
