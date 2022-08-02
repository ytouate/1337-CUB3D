/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:54:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/01 18:09:40 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

// checks the rgb array if it passed 255 or went below 0;
bool	got_overflowed(int *rgb)
{
	int	i;
	i = 0;
	while (i < 3)
	{
		if (rgb[i] > 255 || rgb[i] < 0)
			return (true);
		i++;
	}
	return (false);
}

bool	get_map_rgb(char *line, t_map_data *map_data)
{
	char	**color;
	int		flag;

	flag = 0;
	if (!ft_strncmp(line, "F ", 2))
	{
		color = ft_split(line + 2, ',');
		if (!(color[0] && color[1] && color[2]))
			ft_error(1, "Invalid rgb format\n");
		map_data->floor_color[0] = ft_atoi(color[0]);
		map_data->floor_color[1] = ft_atoi(color[1]);
		map_data->floor_color[2] = ft_atoi(color[2]);
		flag += 1;
		return true;
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		color = ft_split(line + 2, ',');
		if (!(color[0] && color[1] && color[2]))
			ft_error(1, "Invalid rgb format\n");
		map_data->ceilling_color[0] = ft_atoi(color[0]);
		map_data->ceilling_color[1] = ft_atoi(color[1]);
		map_data->ceilling_color[2] = ft_atoi(color[2]);
		flag += 1;
		return true;
	}
	return (false);
}


// skips the empty new lines at the top of the file
// and counts the rest
int count_map_lines(char *map_name)
{
    int		count;
    int		i;
    int		map_fd;
	char	*temp;
	int		flag = 0;

    i = 0;
    count = 0;
	map_fd = open(map_name, O_RDONLY, 0644);
	if (map_fd == -1)
		ft_error(1, "Map not found\n");
	while (true)
	{
		temp = get_next_line(map_fd);
		if (temp == NULL)
			break;
		if (is_valid_line(temp) || count > 0)
			count++;
		free(temp);
	}
	close(map_fd);
	return (count);
}

int count_spaces(char *line)
{
	int i;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

bool	get_texture_path(char *l, t_map_data *map_data)
{
	char *line;
	int		in_between_spaces;

	line = ft_strtrim(l, " \t");
	in_between_spaces = count_spaces(line);
	if (!ft_strncmp(line, "NO ", 3))
	{
		map_data->north_texture = ft_strdup(line + in_between_spaces);
		return (true);
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		map_data->south_texture = ft_strdup(line + in_between_spaces);
		return (true);
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		map_data->west_textrure = ft_strdup(line + in_between_spaces);
		return (true);
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		map_data->east_texture = ft_strdup(line + in_between_spaces);
		return (true);
	}
	// free(line);
	if (get_map_rgb(line, map_data))
		return (true);
	return (false);
}


char **convert_file_to_grid(char *file_name, int file_size)
{
	char	**grid;
	int		i;
	int		map_fd;
	int		flag = 0;
	i = 0;
	map_fd = open(file_name, O_RDONLY);
	if (map_fd == -1)
		ft_error(2, "open failed\n");
	file_size += 1;
	grid = malloc(sizeof(char *) * file_size + 1);
	if (!grid)
		ft_error(2, "Malloc failed map-parse\n");
	while (i < file_size)
	{
		char *temp = get_next_line(map_fd);
		if (!temp)
			break;
		if (is_valid_line(temp) || flag > 0)
		{
			flag += 1;
			grid[i] = ft_strdup(temp);
			printf("%s\n", grid[i]);
			i++;
		}
		free(temp);
	}
	grid[i] = NULL;
	close(map_fd);
	return (grid);
}


// checks if all the map texture is there
void check_map_texture(t_map_data map_data)
{
	if ((!(map_data.north_texture && map_data.south_texture
		&& map_data.east_texture && map_data.west_textrure)))
			ft_error(1, "Invalid map texture\n");
}

