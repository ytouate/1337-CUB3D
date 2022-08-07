/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/07 14:11:17 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
the distance from player to the projection plane is 
160 (the plane width devided by 2) / tan(30(half the fov angle) == 277
320 column = 60 deg
1 colum = 60 / 320
dimension of the projection plane is 320 * 200 units
center of the projection plane (160, 100)
distance to the projection plane 277 units
angle between subsequent rays 60 / 320
*/


// void trace_rays(void)
// {
// 	deg = 30; // half of the fov
// 	while (not_hit_wall())
// 	{
// 		draw_line(x, y);
// 		x += val
// 		y += val
// 	}
// 	// get the distance from the player to the wall
// 	// add the angle increment so that the ray moves to the right
// 	// repeat all that shit 320 merra
// }
//this function for check the zeros not valid in the map;

// void draw_lineofdir(t_mlx_data *data)
// {
// 	int x;
// 	int y;

// 	if (data->player->player_dir == E)
// 	{
// 		x = data->player->player_pos[0] + 4;
// 		ddaline(x, data->player->player_pos[1], x, data->player->player_pos[1] - 40, *data);
// 	}
// 	else if (data->player->player_dir == N)
// 	{
// 		y = data->player->player_pos[1] + 4;
// 		ddaline(data->player->player_pos[0], y, data->player->player_pos[1] + 40, y, *data);
// 	}
// 	else if (data->player->player_dir == S)
// 	{
// 		y = data->player->player_pos[1] + 4;
// 		ddaline(data->player->player_pos[0], y, data->player->player_pos[1] - 40, y, *data);
// 	}
// 	if (data->player->player_dir == W)
// 	{
// 		x = data->player->player_pos[0] + 4;
// 		ddaline(x, data->player->player_pos[1], x, data->player->player_pos[1] + 40, *data);
// 	}
// }

void drawsquare(t_mlx_data *data, int x, int y)
{
	int i;
	int j;

	i = x;
	while (i < x + 63)
	{
		j = y;
		while (j < y + 63)
		{
			my_mlx_pixel_put(data, i, j, 0x808080);
			j++;
		}
		i++;
	}
}

void draw_player(float x, float y, t_mlx_data *data)
{
	int	i;
	int	j;

	i = x;
	while (i < x + 8)
	{
		j = y;
		while (j < y + 8)
		{
			my_mlx_pixel_put(data, i, j, 0x008000);
			j++;
		}
		i++;
	}
	// draw_lineofdir(data);
}

void	lstadd_front(t_vector **lst, t_vector *new)
{
	new ->next = *lst;
	*lst = new;
}

double	get_player_dir(char	c)
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

void draw_map(t_mlx_data *data)
{
	int	i;
	int j;
	float x;
	float y;
	t_vector *borders; 

	borders = malloc(sizeof(t_vector));
	borders->x = -1;
	borders->y = -1;
	borders->next = NULL;
	x = 0;
	y = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		x = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
			{
				t_vector *temp = malloc(sizeof(t_vector));
				temp->x = x;
				temp->y = y;
				temp->next = NULL;
				lstadd_front(&borders, temp);
				drawsquare(data, x, y);
			}
			else if (ft_isalpha(data->map[i][j]))
			{
				data->player->player_pos[0] = x;
				data->player->player_pos[1] = y;
				data->map[i][j] = '0';
				ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
				ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle - data->player->player_half_fov) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle - data->player->player_half_fov) * 50,
					*data, 0xFF0000
				);
				// ddaline(
				// 	data->player->player_pos[0], data->player->player_pos[1],
				// 	data->player->player_pos[0] + sin(data->player->player_angle + data->player->player_half_fov) * 50,
				// 	data->player->player_pos[1] + cos(data->player->player_angle + data->player->player_half_fov) * 50,
				// 	*data, 0xFF00FF
				// );
			}
			x += 64;
			j++;
		}
		i++;
		y += 64 ;
	}
	data->borders = borders;
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
}

int	check_char(char c)
{
	char	*s;
	int		i;

	s = ft_strdup("NSWE10 ");
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			free(s);
			return (1);
		}
		i++;
	}
	free(s);
	return (0);
}

void	check_the_zeros(t_fix_map *map, int i, int j, int len)
{
	if (i == 0 || j == 0 || i == len - 1 || j == map[i].len - 1)
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
	if (j > map[i - 1].len || j > map[i + 1].len)
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
	if (map[i].line_of_map[j + 1] == ' ' || map[i].line_of_map[j - 1] == ' ' )
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
	if (map[i - 1].line_of_map[j] == ' ' || map[i + 1].line_of_map[j] == ' ' )
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
}

void	call_check_zeros(t_fix_map *map, int len)
{
	int	i;
	int j;
	int	flag;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (map[i].len == 0)
			flag = -1;
		else
			flag = 0;
		if (map[i].len == 0 && i < len - 1)
			ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
		while (map[i].line_of_map[j])
		{
			if (check_char(map[i].line_of_map[j]) == 0)
				ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
			if (map[i].line_of_map[j] == '0')
				check_the_zeros(map, i, j, len);
			j++;
		}
		i++;
	}
	if (flag == -1)
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
}

//this function for fill the map with lens
void	check_all_the_map(t_map_data map_data)
{
	t_fix_map	*map_with_len;
	int			i;

	i = 0;
	map_with_len = malloc(sizeof(t_fix_map) * map_data.map_lines + 2);
	while (map_data.map[i])
	{
		map_with_len[i].len = ft_strlen(map_data.map[i]);
		map_with_len[i].line_of_map = map_data.map[i];
		i++;
	}
	call_check_zeros(map_with_len, map_data.map_lines);
}

bool got_collided(t_mlx_data *data)
{
	while (data->borders)
	{
		if ((data->borders->x > data->player->player_pos[0] || data->borders->y < data->player->player_pos[0])
			&& data->borders->y == data->player->player_pos[1])
			return (true);
		data->borders = data->borders->next;
	}
	return (false);
}

int rotate_player(int keycode,t_mlx_data *data)
{
	if (keycode == LEFT)
	{
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
	}
	else if (keycode == RIGHT)
	{
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
		draw_map(data);
	}
	else if (keycode == UP) 
	{
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
	}
	else if (keycode == BOTTOM)
	{
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
	}
	return (0);
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
	else if (D_KEY == keycode)
	{
		data->player->player_pos[0] += 64;
		mlx_clear_window(data->mlx_ptr, data->window);
		data->img = mlx_new_image(data->mlx_ptr, data->window_x_size, data->window_y_size);
		data->addr = mlx_get_data_addr(data->img,
		&data->bits_per_pixel, &data->line_size, &data->endian);
		draw_player(data->player->player_pos[0], data->player->player_pos[1], data);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle - data->player->player_half_fov) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle - data->player->player_half_fov) * 50,
					*data, 0xFF0000
				);
		draw_map(data);
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
	}
	else if (W_KEY == keycode)
	{
		mlx_clear_window(data->mlx_ptr, data->window);
		data->img = mlx_new_image(data->mlx_ptr, data->window_x_size, data->window_y_size);
		data->addr = mlx_get_data_addr(data->img,
		&data->bits_per_pixel, &data->line_size, &data->endian);
		data->player->player_pos[1] -= 64;
		draw_player(data->player->player_pos[0], data->player->player_pos[1], data);
		draw_map(data);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle - data->player->player_half_fov) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle - data->player->player_half_fov) * 50,
					*data, 0xFF0000
				);
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
	}
	else if (A_KEY == keycode)
	{
		mlx_clear_window(data->mlx_ptr, data->window);
		data->img = mlx_new_image(data->mlx_ptr, data->window_x_size, data->window_y_size);
		data->addr = mlx_get_data_addr(data->img,
		&data->bits_per_pixel, &data->line_size, &data->endian);
		data->player->player_pos[0] -= 64;
		draw_player(data->player->player_pos[0], data->player->player_pos[1], data);
		draw_map(data);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle - data->player->player_half_fov) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle - data->player->player_half_fov) * 50,
					*data, 0xFF0000
				);
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
	}
	else if (S_KEY == keycode)
	{
		mlx_clear_window(data->mlx_ptr, data->window);
		data->img = mlx_new_image(data->mlx_ptr, data->window_x_size, data->window_y_size);
		data->addr = mlx_get_data_addr(data->img,
		&data->bits_per_pixel, &data->line_size, &data->endian);
		data->player->player_pos[1] += 64;
		draw_player(data->player->player_pos[0], data->player->player_pos[1], data);
		draw_map(data);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle) * 50,
					*data, 0xFF0000
				);
		ddaline(
					data->player->player_pos[0], data->player->player_pos[1],
					data->player->player_pos[0] + sin(data->player->player_angle - data->player->player_half_fov) * 50,
					data->player->player_pos[1] + cos(data->player->player_angle - data->player->player_half_fov) * 50,
					*data, 0xFF0000
				);
		mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
	}
	// rotate_player(keycode, data);
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

void	data_constructor(t_mlx_data *mlx_data, t_map_data *map_data)
{
	map_data_constructor(map_data);
	mlx_data->mlx_ptr = mlx_init();

	
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

// checks if all the string contains digits
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

// fill the map_data from the file
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

void fill_map(t_map_data *map_data, t_mlx_data *mlx_data)
{
	char **temp_grid;
	int	map_content_start;
	int map_content_end;
	int i;
	
	temp_grid = convert_file_to_grid(map_data->map_name, map_data->map_lines);
	map_content_start = fill_map_data(temp_grid, map_data);
	map_content_end = map_data->map_lines;
	map_data->map = malloc(sizeof(char *) * map_content_end - map_content_start + 1);
	i = 0;
	while (temp_grid[map_content_start])
	{
		char *temp = ft_strtrim(temp_grid[map_content_start++], "\n");
		map_data->map[i++] = ft_strdup(temp);
		free(temp);
	}
	map_data->map[i] = temp_grid[map_content_start];
	map_data->map_lines = i;
	mlx_data->window_x_size = ft_strlen(map_data->map[0]) * 64;
	mlx_data->window_y_size = map_data->map_lines  * 64;
	free_grid(temp_grid);
}

void init(t_mlx_data *mlx_data, t_map_data *map_data)
{
	data_constructor(mlx_data, map_data);
	
	map_data->map_lines = count_map_lines(map_data->map_name);
	if (map_data->map_lines == 0)
		ft_error(UNEXPECTED_FLOW, "Empty Map\n");
}

void init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->window = mlx_new_window(mlx_data->mlx_ptr, mlx_data->window_x_size,
					mlx_data->window_y_size, "Cub3D");
	mlx_data->img = mlx_new_image(mlx_data->mlx_ptr, mlx_data->window_x_size,
					mlx_data->window_y_size);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img,
				&mlx_data->bits_per_pixel, &mlx_data->line_size, &mlx_data->endian);
	mlx_data->player = malloc(sizeof(t_player));
	mlx_data->player->player_pos[0] = -1;
	mlx_data->player->player_pos[1] = -1;
	mlx_data->player->player_dir = 0;
}

int	main(int ac, char **av)
{
	
	char	**temp_grid;
	t_mlx_data mlx_data;
	t_map_data map_data;

	map_data.map_name = av[1];
	check_basic_requirements(ac, av);
	init(&mlx_data, &map_data);
	fill_map(&map_data, &mlx_data);
	init_mlx(&mlx_data);
	check_all_the_map(map_data);
	mlx_data.player->player_fov = PI / 3;
	mlx_data.player->player_half_fov = mlx_data.player->player_fov / 2;
	mlx_data.player->player_angle = PI;
	mlx_data.map = map_data.map;
	mlx_data.player->player_pos[0] = -1;
	mlx_data.player->player_pos[1] = -1;
	draw_map(&mlx_data);
	// mlx_key_hook(mlx_data.window, hook_into_key_events, &mlx_data);
	mlx_hook(mlx_data.window, KEYPRESS, KEYPRESSMASK, hook_into_key_events, &mlx_data);
	mlx_hook(mlx_data.window, KEYRELEASE, KEYRELEASEMASK, rotate_player, &mlx_data);
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
}
