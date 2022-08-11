/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 11:50:40 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
				map_data->north_texture = ft_strdup(line + spaces);
			}
			else if (!ft_strncmp("SO ", line, 3))
			{
				check[1] += 1;
				map_data->south_texture = ft_strdup(line + spaces);
			}
			else if (!ft_strncmp("WE ", line, 3))
			{
				check[2] += 1;
				map_data->west_textrure = ft_strdup(line + spaces);
			}
			else if (!ft_strncmp("EA ", line, 3))
			{
				check[3] += 1;
				map_data->east_texture = ft_strdup(line + spaces);
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
	free_grid(temp_grid);
}

void init(t_mlx_data *mlx_data, t_map_data *map_data)
{
	map_data_constructor(map_data);
	mlx_data->player.x = WINDOW_WIDTH / 2;
	mlx_data->player.y = WINDOW_HEIGHT / 2;

	mlx_data->rays.width = TILE_SIZE; 
	mlx_data->rays.height = TILE_SIZE;
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data == NULL)
		ft_error(FUNCTION_FAILED, "mlx_init() FAILED \n");
	map_data->map_lines = count_map_lines(map_data->map_name);
	if (map_data->map_lines == 0)
		ft_error(UNEXPECTED_FLOW, "Empty Map\n");
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
	mlx_data.map = map_data.map;
	render(&mlx_data);
	mlx_hook(mlx_data.window, KEYPRESS, KEYPRESSMASK, hook_into_key_events, &mlx_data);
	mlx_hook(mlx_data.window, KEYRELEASE, KEYRELEASEMASK, rotate_player, &mlx_data);
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data); 
	mlx_loop(mlx_data.mlx_ptr);
}
