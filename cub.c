/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/08 17:50:59 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void ft_draw_player(t_mlx_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->window);
	data->img = mlx_new_image(data->mlx_ptr, data->window_x_size, data->window_y_size);
	data->addr = mlx_get_data_addr(data->img,
	&data->bits_per_pixel, &data->line_size, &data->endian);
	// draw_player(data->player.x, data->player.y, data);
	draw_map(data);
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle) * 50,
		data->player.y + cos(data->player.rotation_angle) * 50,
		*data, 0xFF0000
	);
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle - HALF_FOV) * 50,
		data->player.y + cos(data->player.rotation_angle - HALF_FOV) * 50,
		*data, 0xFF0000
	);
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle + HALF_FOV) * 50,
		data->player.y + cos(data->player.rotation_angle + HALF_FOV) * 50,
		*data, 0xFF0000
	);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
}

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
	while (i < x + 10)
	{
		j = y;
		while (j < y + 10)
		{
			my_mlx_pixel_put(data, i, j, 0x008000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
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
				data->player.x = x;
				data->player.y = y;
				data->map[i][j] = '0';
				
				ft_draw_player(data);
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
	flag = 0;
	while (i < len)
	{
		j = 0;
		if (map[i].len == 0 && i < len - 1 && map[i + 1].len > 0)
			ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
		while (map[i].line_of_map[j])
		{
			if (check_char(map[i].line_of_map[j]) == 0)
				ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
			if (map[i].line_of_map[j] == '0' || ft_isalpha(map[i].line_of_map[j]))
				check_the_zeros(map, i, j, len);
			if (ft_isalpha(map[i].line_of_map[j]))
				flag += 1;
			j++;
		}
		i++;
	}
	if (flag != 1)
		ft_error(UNEXPECTED_FLOW, "INVALID MAP\n");
}

//this function for fill the map with lens
void	check_all_the_map(t_map_data map_data)
{
	t_fix_map	*map_with_len;
	int			i;

	i = 0;
	map_with_len = malloc(sizeof(t_fix_map) * map_data.map_lines);
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
		if ((data->borders->x > data->player.x || data->borders->y < data->player.x)
			&& data->borders->y == data->player.y)
			return (true);
		data->borders = data->borders->next;
	}
	return (false);
}

int rotate_player(int keycode,t_mlx_data *data)
{
	if (keycode == LEFT)
	{
		data->player.rotation_angle -= 0.1;
		ft_draw_player(data);
	}
	else if (keycode == RIGHT)
	{
		data->player.rotation_angle += 0.1;
		ft_draw_player(data);
	}
	else if (keycode == UP) 
	{
		
		ddaline(
					data->player.x, data->player.y,
					data->player.x - sin(data->player.rotation_angle) * 50,
					data->player.y + cos(data->player.rotation_angle) * 50,
					*data, 0xFF0000
				);
	}
	else if (keycode == BOTTOM)
	{
		ddaline(
					data->player.x, data->player.y,
					data->player.x - sin(data->player.rotation_angle) * 50,
					data->player.y + cos(data->player.rotation_angle) * 50,
					*data, 0xFF0000
				);
	}
	return (0);
}

// the key handler function;
int	hook_into_key_events(int keycode, t_mlx_data *data)
{
	data->player.x += 0;
	data->player.y += 1;
	return (0);
	// if (keycode == ESC)
	// {
	// 	mlx_destroy_window(data->mlx_ptr, data->window);
	// 	//TODO:
	// 		// Free all the resources;
	// 	exit(EXIT_SUCCESS);
	// }
	// else if (D_KEY == keycode)
	// {
	// 	data->player.x += 32;
	// 	printf("%f\n", data->player.x);
	// 	printf("%f\n", data->player.y);
	// 	ft_draw_player(data);
	// 	draw_map(data);
	// }
	// else if (W_KEY == keycode)
	// {
		
	// 	data->player.y -= 32;
	// 	ft_draw_player(data);
	// 	draw_map(data);
	// }
	// else if (A_KEY == keycode)
	// {
	// 	data->player.x -= 32;
	// 	ft_draw_player(data);
	// 	draw_map(data);
	// }
	// else if (S_KEY == keycode)
	// {
	// 	data->player.y += 32;
	// 	ft_draw_player(data);
	// 	draw_map(data);
	// }
	// return (0);
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
	ft_memset(map_data->ceilling_color, -1, 3 * sizeof(int));
	ft_memset(map_data->floor_color, -1, 3 * sizeof(int));
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
	printf("%sa\n", map_data.north_texture);
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

char	*fill_the_path(char *line)
{
	int		i;
	char	*s;
	char	*temp;
	char	l;

	s = ft_strdup("");
	i = 0;
	while (line[i])
	{
		temp = s;
		l = line[i];
		s = ft_strjoin(s, m);
		free(temp);
		i++;
		if (line[i] == ' ' && line[i - 1] != '\\')
			return (s);
	}
	return (s);
}
// fill the first sex lines;
int	fill_map_data(char **grid, t_map_data *map_data)
{
	int	i;
	char *line;
	int spaces;
	int		*check;

	i = 0;
	check = malloc(sizeof(int) * 6);
	ft_memset(check, 0, sizeof(int) * 6);
	while (grid[i])
	{
		if (is_valid_line(grid[i])){
			line = ft_strtrim(grid[i], "\n\t");
			spaces = count_spaces(line);
			if (!ft_strncmp("NO ", line, 3))
			{
				check[0] += 1;
				map_data->north_texture = fill_the_path(line + spaces);
			}
			else if (!ft_strncmp("SO ", line, 3))
			{
				check[1] += 1;
				map_data->south_texture = fill_the_path(line + spaces);
			}
			else if (!ft_strncmp("WE ", line, 3))
			{
				check[2] += 1;
				map_data->west_textrure = fill_the_path(line + spaces);
			}
			else if (!ft_strncmp("EA ", line, 3))
			{
				check[3] += 1;
				map_data->east_texture = fill_the_path(line + spaces);
			}
			else if (!ft_strncmp("F ", line, 2))
			{
				check[4] += 1;
				fill_rgb_array(line, map_data->floor_color);
			}
			else if (!ft_strncmp("C ", line, 2))
			{
				check[5] += 1;
				fill_rgb_array(line, map_data->ceilling_color);
			}
			else
			{
				int j = 0;
				while (j < 6)
				{
					if (check[j] != 1)
						return (-1);
					j++;
				}
				return (i);
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
	if (map_content_start == -1)
		ft_error(UNEXPECTED_FLOW, "the elements are not valid");
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
	mlx_data->window_x_size = 800;
	mlx_data->window_y_size = 600;
	free_grid(temp_grid);
}

void init(t_mlx_data *mlx_data, t_map_data *map_data)
{
	map_data_constructor(map_data);
	mlx_data->player.x = 0;
	mlx_data->player.y = 0;
	
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data == NULL)
		ft_error(FUNCTION_FAILED, "mlx_init() FAILED \n");
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
	mlx_data->player.x = -1;
	mlx_data->player.y = -1;
}

double deg2rad(double degrees) {
	return (degrees * (PI / 180.0));
}

double rad2deg(double radian) {
	return (radian / (PI / 180.0));
}

void render(t_mlx_data *data) {
	// TODO:
		// RENDER ALL THE GAME OBJECTS FOR THE CURRENT FRAME
	
}

int	main(int ac, char **av)
{
	t_mlx_data mlx_data;
	t_map_data map_data;

	map_data.map_name = av[1];
	check_basic_requirements(ac, av);
	init(&mlx_data, &map_data);
	fill_map(&map_data, &mlx_data);
	init_mlx(&mlx_data);
	check_all_the_map(map_data);
	show_map_data(map_data);
	// mlx_data.rays = malloc(sizeof(t_rays));
	// mlx_data.player.player_angle = PI;
	mlx_data.map = map_data.map;
	mlx_data.player.x = 0;
	mlx_data.player.y = 0;
	draw_player(mlx_data.player.x,
		mlx_data.player.y, &mlx_data);
	// mlx_hook(mlx_data.window, KEYPRESS, KEYPRESSMASK, hook_into_key_events, &mlx_data);
	// mlx_hook(mlx_data.window, KEYRELEASE, KEYRELEASEMASK, rotate_player, &mlx_data);
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data); 
	mlx_loop(mlx_data.mlx_ptr);
}
