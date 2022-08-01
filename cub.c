/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/01 11:54:56 by ytouate          ###   ########.fr       */
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

// closes the window when the red button is clicked
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
	map_data->north_texture = NULL;
	map_data->west_textrure = NULL;
	map_data->south_texture = NULL;
	map_data->east_texture = NULL;
	map_data->map_lines = -1;
	ft_memset(map_data->ceilling_color, 0, 3 * sizeof(int));
	ft_memset(map_data->floor_color, 0, 3 * sizeof(int));
}

// returns true if the line send to it contain some content
bool	is_valid_line(char *line)
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

// skips the gap between the map rgb/texture and the map content
void	skip_empty_lines(char **grid, int *n, int map_len)
{
	if (*n == map_len)
		ft_error(1, "The map should be at the bottom of the file\n");
	while (grid[*n])
	{
		if (is_valid_line(grid[*n]))
			return;
		*n += 1;
	}
}

// frees the 2d grid passed to it
void	free_grid(char **grid)
{
	int i;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}


void print_grid(char **s){
	int i = 0;
	while (s[i])
		printf("%s\n", s[i++]);
}

void show_map_data(t_map_data map_data)
{
	printf("======================the map======================\n");
	print_grid(map_data.map);
	printf("the textures\n");
	printf("%s\n", map_data.north_texture);
	printf("%s\n", map_data.south_texture);
	printf("%s\n", map_data.west_textrure);
	printf("%s\n", map_data.east_texture);
	printf("the floor colors\n");
	for (int i = 0; i < 3; i++)
		printf("%d\t", map_data.floor_color[i]);
	printf("\n");
	printf("the ceiling colors\n");
	for (int i = 0; i < 3; i++)
		printf("%d\t", map_data.ceilling_color[i]);
	printf("\n");
	
}

int	main(int ac, char **av)
{
	t_mlx_data	mlx_data;
	t_map_data	map_data;

	map_data_consructor(&map_data);
	char	**temp_grid;
	mlx_data.mlx_ptr = mlx_init();
	mlx_data.window_x_size = 600;
	mlx_data.window_y_size = 350;
	if (ac < 2)
		ft_error(1, "A Map file-name is required !\n");
	if (!check_file_extention(av[1]))
		ft_error(1, "the file extention is not .cub\n");
	map_data.map_lines = count_map_lines(av[1]);
	temp_grid = convert_file_to_grid(av[1], map_data.map_lines);
	
	int	flag = 0;
	int	i;
	for (i = 0; temp_grid[i]; i++)
	{
		if (get_texture_path(temp_grid[i], &map_data))
			flag += 1;
		if (flag == 6)
			break;
	}
	if (got_overflowed(map_data.ceilling_color)
		|| got_overflowed(map_data.floor_color))
		ft_error(1, "Invalid rgb numbers\n");
	if (flag != 6)
		ft_error(1, "the map requirments are not fullfilled\n");
	int start = i + 1;
	skip_empty_lines(temp_grid, &start, map_data.map_lines);
	int	end = map_data.map_lines - start;
	map_data.map = malloc(sizeof(char *) * end + 2);
	if (!map_data.map)
		ft_error(1, "Malloc Failed\n");
	i = 0;
	while (temp_grid[start])
		map_data.map[i++] = ft_strdup(temp_grid[start++]);
	map_data.map[i] = temp_grid[start];
	map_data.map_lines = i;
	check_map_borders(map_data);
	free_grid(temp_grid);
	check_map_texture(map_data);
	mlx_data.window = mlx_new_window(mlx_data.mlx_ptr, mlx_data.window_x_size, mlx_data.window_y_size, "Cub3D");
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data); 
	mlx_key_hook(mlx_data.window, hook_into_key_events, &mlx_data);
	void *img = mlx_new_image(mlx_data.mlx_ptr, mlx_data.window_x_size, mlx_data.window_y_size);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.window, img, 0, 0);
	show_map_data(map_data);
	mlx_loop(mlx_data.mlx_ptr);
}
