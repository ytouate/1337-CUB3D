/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:54:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 10:53:38 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/* 
	**checks if there is a map file-name
	**in the av and checks if the file name is valid
*/

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
bool	is_number(char *s)
{
	int	i;
	int	len;

	i = 0;
	s = ft_strtrim(s, " ");
	len = ft_strlen(s);
	while (i < len)
	{
		if (!ft_isdigit(s[i++]))
		{
			free(s);
			return (false);
		}
	}
	free(s);
	return (true);
}

//count the commas in rgb;
void	count_commas(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		ft_error(UNEXPECTED_FLOW, "INVALID RGB FORMAT\n");
}

void	convert_to_int(char **temp, int *arr)
{
	int		i;

	i = -1;
	if (temp[0] && temp[1] && temp[2])
	{
		if (is_number(temp[0]) && is_number(temp[1]) && is_number(temp[2]))
		{
			arr[0] = ft_atoi(temp[0]);
			arr[1] = ft_atoi(temp[1]);
			arr[2] = ft_atoi(temp[2]);
			while (++i < 3)
				if (arr[i] > 255 || arr[i] < 0)
					ft_error(UNEXPECTED_FLOW, "RGB OVERFLOW OR UNDERFLOW\n");
		}
		else
		{
			free_grid(temp);
			ft_error(UNEXPECTED_FLOW, "INVALID RGB COLORS\n");
		}
	}
	else
	{
		free_grid(temp);
		ft_error(UNEXPECTED_FLOW, "INVALID RGB FORMAT\n");
	}
}
// fills the rgb array and checks if the colors are valid;

void	fill_rgb_array(char *line, int *arr)
{
	char	**temp;
	int		i;
	char	*str;
	char	*t;

	i = 0;
	str = ft_strdup(line + 1);
	while (str[i] == ' ')
		i++;
	t = str;
	str = ft_strdup(str + i);
	free(t);
	count_commas(str);
	temp = ft_split(str, ',');
	free(str);
	convert_to_int(temp, arr);
	free_grid(temp);
}

char	*get_path(int i, char *str)
{
	char		*s;
	int			j;

	j = 0;
	s = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	while (str[j])
	{
		if (str[j] != ' ')
			ft_error(UNEXPECTED_FLOW, "wrong path !!\n");
		j++;
	}
	free(str);
	s[j] = '\0';
	return (s);
}

//fill the textures;
char	*fill_the_path(char *line)
{
	int		i;
	char	*s;
	int		j;
	char	*str;

	i = 0;
	str = ft_strdup(line + 2);
	while (str[i] == ' ')
		i++;
	s = str;
	str = ft_strdup(s + i);
	free(s);
	i = 0;
	j = 0;
	while (str[i])
	{
		i++;
		if (str[i] == ' ' && str[i - 1] != '\\')
			break ;
	}
	return (get_path(i, str));
}

void	first_conditions(t_mlx_data *data, char *line, int spaces, int *check)
{
	if (!ft_strncmp("NO ", line + spaces, 3))
	{
		check[0] += 1;
		if (check[0] > 1)
			ft_error(UNEXPECTED_FLOW, "multiple textures\n");
		check[6] += 1;
		data->map_data.north_texture = fill_the_path(line + spaces);
	}
	else if (!ft_strncmp("SO ", line + spaces, 3))
	{
		check[1] += 1;
		if (check[1] > 1)
			ft_error(UNEXPECTED_FLOW, "multiple textures\n");
		check[6] += 1;
		data->map_data.south_texture = fill_the_path(line + spaces);
	}
	else if (!ft_strncmp("WE ", line + spaces, 3))
	{
		check[2] += 1;
		if (check[2] > 1)
			ft_error(UNEXPECTED_FLOW, "multiple textures\n");
		check[6] += 1;
		data->map_data.west_textrure = fill_the_path(line + spaces);
	}
}

void	second_conditions(t_mlx_data *data, char *line, int spaces, int *check)
{
	if (!ft_strncmp("EA ", line + spaces, 3))
	{
		check[3] += 1;
		if (check[3] > 1)
			ft_error(UNEXPECTED_FLOW, "multiple textures\n");
		check[6] += 1;
		data->map_data.east_texture = fill_the_path(line + spaces);
	}
	else if (!ft_strncmp("F ", line + spaces, 2))
	{
		check[4] += 1;
		check[6] += 1;
		fill_rgb_array(line + spaces, data->map_data.floor_color);
	}
	else if (!ft_strncmp("C ", line + spaces, 2))
	{
		check[5] += 1;
		check[6] += 1;
		fill_rgb_array(line + spaces, data->map_data.ceilling_color);
	}
	else if (check[6] == 0)
		ft_error(UNEXPECTED_FLOW, "invalid elements\n");
}

// fill the first sex lines;
int	check_the_array(int *check, int i)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (check[j] != 1)
			return (-1);
		j++;
	}
	return (i);
}

int	fill_map_data(char **grid, t_mlx_data *data)
{
	int		i;
	char	*line;
	int		spaces;
	int		check[7];

	i = 0;
	ft_memset(check, 0, sizeof(int) * 7);
	while (grid[i])
	{
		if (is_valid_line(grid[i]))
		{
			line = ft_strtrim(grid[i], "\n\t");
			spaces = count_spaces(line);
			if (ft_isalpha(line[spaces]))
			{
				check[6] = 0;
				first_conditions(data, line, spaces, check);
				second_conditions(data, line, spaces, check);
				free(line);
			}
			else
			{
				free(line);
				return (check_the_array(check, i));
			}
		}
		i++;
	}
	return (-1);
}

// fill the map_data from the file
void	fill_map(t_mlx_data *data)
{
	char	**temp_grid;
	int		map_content_start;
	int		map_content_end;
	int		i;
	char	*temp;

	temp_grid = convert_file_to_grid(data);
	map_content_start = fill_map_data(temp_grid, data);
	if (map_content_start == -1)
		ft_error(UNEXPECTED_FLOW, "the elements are not valid\n");
	map_content_end = data->map_data.map_lines;
	data->map_data.map = ft_calloc(sizeof(char *),
			map_content_end - map_content_start + 1);
	i = 0;
	while (temp_grid[map_content_start])
	{
		temp = ft_strtrim(temp_grid[map_content_start++], "\n");
		data->map_data.map[i++] = ft_strdup(temp);
		free(temp);
	}
	data->map_data.map[i] = temp_grid[map_content_start];
	data->map_data.map_lines = i;
	free_grid(temp_grid);
}

// and counts the rest
int		count_map_lines(char *map_name)
{
	int		count;
	int		i;
	int		map_fd;
	char	*temp;

	i = 0;
	count = 0;
	map_fd = open(map_name, O_RDONLY, 0644);
	if (map_fd == -1)
		ft_error(1, "Map not found\n");
	while (true)
	{
		temp = get_next_line(map_fd);
		if (temp == NULL)
			break ;
		if (is_valid_line(temp) || count > 0)
			count++;
		free(temp);
	}
	close(map_fd);
	return (count);
}

int	count_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n' || line[i] == '\t'))
		i++;
	return (i);
}

void	fill_grid_with_map_lines(char **grid, t_mlx_data *data, int map_fd)
{
	int		i;
	int		flag;
	char	*temp;

	i = 0;
	flag = 0;
	while (i < data->map_data.map_lines)
	{
		temp = get_next_line(map_fd);
		if (!temp)
			break ;
		if (is_valid_line(temp) || flag > 0)
		{
			flag += 1;
			grid[i] = ft_strdup(temp);
			i++;
		}
		free(temp);
	}
	grid[i] = NULL;
}

char	**convert_file_to_grid(t_mlx_data *data)
{
	char	**grid;
	int		i;
	int		map_fd;

	i = 0;
	data->map_data.map_lines = count_map_lines(data->map_data.map_name);
	map_fd = open(data->map_data.map_name, O_RDONLY);
	if (map_fd == -1)
		ft_error(2, "open failed\n");
	data->map_data.map_lines += 1;
	grid = malloc(sizeof(char *) * data->map_data.map_lines + 1);
	if (!grid)
		ft_error(2, "Malloc failed map-parse\n");
	fill_grid_with_map_lines(grid, data, map_fd);
	close(map_fd);
	return (grid);
}

// checks if all the map texture is there
void	check_map_texture(t_map_data map_data)
{
	if ((!(map_data.north_texture
				&& map_data.south_texture
				&& map_data.east_texture
				&& map_data.west_textrure)))
	{
		ft_error(1, "Invalid map texture\n");
	}
}
