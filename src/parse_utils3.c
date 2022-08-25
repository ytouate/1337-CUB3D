/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:12:37 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/25 13:12:38 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	count_map_lines(char *map_name)
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
