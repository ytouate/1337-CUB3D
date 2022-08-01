/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/01 18:09:45 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FUNCTION_FAILED 2
#define UNEXPECTED_FLOW 1

//this function for check the zeros not valid in the map;
void	check_the_zeros(char **map, int i, int j)
{
	if (i == 0 || j == 0 || map[i+1] == NULL || map[i][j + 1] == '\0')
	{
		write(3, "the map is not valid", 21);
		exit(EXIT_FAILURE);
	}
	if (map[i+1][j] == ' ' || map[i-1][j] == ' ')
	{
		write(3, "the map is not valid", 21);
		exit(EXIT_FAILURE);
	}
	else if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
	{
		write(3, "the map is not valid", 21);
		exit(EXIT_FAILURE);
	}
}

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

// returns true if the file passed to it ends with .cub
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
void	map_data_constructor(t_map_data *map_data)
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
	// printf("======================the map======================\n");
	// print_grid(map_data.map);
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

void	data_constructor(t_mlx_data *mlx_data, t_map_data *map_data)
{
	map_data_constructor(map_data);
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->window_x_size = 800;
	mlx_data->window_y_size = 900;
	mlx_data->window = mlx_new_window(mlx_data->mlx_ptr, mlx_data->window_x_size,
					mlx_data->window_y_size, "Cub3D");
	mlx_data->img = mlx_new_image(mlx_data->mlx_ptr, mlx_data->window_x_size, mlx_data->window_y_size);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img,
		&mlx_data->bits_per_pixel, &mlx_data->line_size, &mlx_data->endian);
}

// checks if there is a map file-name in the av and checks if the file name is valid
void	check_basic_requirements(int ac, char **av)
{
	if (ac != 2)
		ft_error(UNEXPECTED_FLOW, "A MAP NAME IS REQUIRED !\n");
	else
		if (!check_file_extention(av[1]))
			ft_error(UNEXPECTED_FLOW, "THE MAP FILE-NAME MUST END WITH .cub\n");
}

// returns true if the map identifiers are valid
bool	check_map_identifiers(char *line)
{
	return (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("F ", line, 2) || !ft_strncmp("C ", line, 2));
}

bool is_number(char *s)
{
	int i;
	i = 0;
	int len;
	
	s = ft_strtrim(s, " ");
	len = ft_strlen(s);
	while (i < len)
	{
		if (!ft_isdigit(s[i++]))
			return (false);
	}
	return (true);
}

// fills the rgb array and checks if the colors are valid;
void	fill_rgb_array(char *line, int *arr)
{
	char **temp;
	int spaces;
	int i;

	i = -1;
	spaces = count_spaces(line);
	temp = ft_split(line + spaces, ',');
	if (temp[0] && temp[1] && temp[2])
	{
		if (is_number(temp[0]) && is_number(temp[1]) && is_number(temp[2]))
		{
			arr[0] = ft_atoi(temp[0]);
			arr[1] = ft_atoi(temp[1]);
			arr[2] = ft_atoi(temp[2]);
			while (++i < 3)
				if (arr[i] > 255  || arr[i] < 0)
					ft_error(UNEXPECTED_FLOW, "RGB OVERFLOW OR UNDERFLOW\n");
		}
		else
		{
			ft_error(UNEXPECTED_FLOW, "INVALID RGB COLORS\n");
		}
	}
	else
		ft_error(UNEXPECTED_FLOW, "INVALID RGB FORMAT\n");
}

// fill the first sex lines;
int	fill_map_data(char **grid, t_map_data *map_data)
{
	int	i;
	char *line;
	int	flag;
	int spaces;

	flag = 0;
	i = 0;
	while (grid[i])
	{
		if (is_valid_line(grid[i])){
			line = ft_strtrim(grid[i], "\n \t");
			flag += check_map_identifiers(line);
			spaces = count_spaces(line);
			if (!ft_strncmp("NO ", line, 3))
				map_data->north_texture = ft_strdup(line + spaces);
			else if (!ft_strncmp("SO ", line, 3))
				map_data->south_texture = ft_strdup(line + spaces);
			else if (!ft_strncmp("WE ", line, 3))
				map_data->west_textrure = ft_strdup(line + spaces);
			else if (!ft_strncmp("EA ", line, 3))
				map_data->east_texture = ft_strdup(line + spaces);
			else if (!ft_strncmp("F ", line, 2))
				fill_rgb_array(line, map_data->floor_color);
			else if (!ft_strncmp("C ", line, 2))
				fill_rgb_array(line, map_data->ceilling_color);
			else
			{
				if (flag == 6)
					return (i);
				ft_error(UNEXPECTED_FLOW, "UNEXPECTED/MISSING MAP IDENTIFIER\n");
			}
		}
		i++;
	}
	return (-1);
}


void init_map_data(t_map_data *map_data)
{
	int map_content_start;
	char **temp_grid;
	int	map_content_end = map_data->map_lines;
	int i;
	char *temp;

	i = 0;
	temp_grid = convert_file_to_grid(map_data->map_name, map_data->map_lines);
	map_content_start = fill_map_data(temp_grid, map_data);
	map_data->map = malloc(sizeof(char *) * map_data->map_lines - map_content_start + 1);
	while (temp_grid[map_content_start])
	{
		temp = ft_strtrim(temp_grid[map_content_start++], "\n");
		map_data->map[i++] = temp;
		free(temp);
	}
	map_data->map[i] = temp_grid[map_content_start];
	free_grid(temp_grid);
	map_data->map_lines = i;
}

int	main(int ac, char **av)
{
	t_mlx_data	mlx_data;
	t_map_data	map_data;
	char	**temp_grid;

	check_basic_requirements(ac, av);
	data_constructor(&mlx_data, &map_data);
	map_data.map_name = av[1];
	map_data.map_lines = count_map_lines(map_data.map_name);
	if (map_data.map_lines == 0)
		ft_error(UNEXPECTED_FLOW, "Empty Map\n");
	init_map_data(&map_data);
	show_map_data(map_data);
	mlx_key_hook(mlx_data.window, hook_into_key_events, &mlx_data);
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}
