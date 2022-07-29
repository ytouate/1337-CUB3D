/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:54:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/29 10:08:34 by ytouate          ###   ########.fr       */
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

void	get_map_rgb(char *line, t_map_data *map_data)
{
	char	**color;

	if (!ft_strncmp(line, "F ", 2))
	{
		color = ft_split(line + 2, ',');
		if (!(color[0] && color[1] && color[2]))
			ft_error(1, "Invalid rgb format\n");
		map_data->floor_color[0] = ft_atoi(color[0]);
		map_data->floor_color[1] = ft_atoi(color[1]);
		map_data->floor_color[2] = ft_atoi(color[2]);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		color = ft_split(line + 2, ',');
		if (!(color[0] && color[1] && color[2]))
			ft_error(1, "Invalid rgb format\n");
		map_data->ceilling_color[0] = ft_atoi(color[0]);
		map_data->ceilling_color[1] = ft_atoi(color[1]);
		map_data->ceilling_color[2] = ft_atoi(color[2]);
	}
	if (got_overflowed(map_data->ceilling_color) || got_overflowed(map_data->floor_color))
		ft_error(1, "Invalid rgb numbers\n");
}

int count_map_lines(char *map_name)
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
			break;
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

void	get_texture_path(char *l, t_map_data *map_data)
{
	char *line;
	int		in_between_spaces;

	line = ft_strtrim(l, " \t");
	in_between_spaces = count_spaces(line);
	if (!ft_strncmp(line, "NO ", 3))
		map_data->north_texture = ft_strdup(line + in_between_spaces);
	if (!ft_strncmp(line, "SO ", 3))
		map_data->south_texture = ft_strdup(line + in_between_spaces);
	if (!ft_strncmp(line, "WE ", 3))
		map_data->west_textrure = ft_strdup(line + in_between_spaces);
	if (!ft_strncmp(line, "EA ", 3))
		map_data->east_texture = ft_strdup(line + in_between_spaces);
	get_map_rgb(line, map_data);
	free(line);
}


char **convert_file_to_grid(char *file_name, int file_size)
{
	char	**grid;
	int		i;
	int		map_fd;

	i = 0;
	file_size = count_map_lines(file_name);
	map_fd = open(file_name, O_RDONLY);
	if (map_fd == -1)
		ft_error(2, "open failed\n");
	grid = malloc(sizeof(char *) * file_size + 1);
	if (!grid)
		ft_error(2, "Malloc failed map-parse\n");

	while (i < file_size)
	{
		grid[i] = get_next_line(map_fd);
		i++;
	}
	grid[i - 1] = NULL;
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

