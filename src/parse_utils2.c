/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:07:23 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/25 13:07:28 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

void	check_element(int spaces, int *check, t_mlx_data *data, char *line)
{
	check[6] = 0;
	first_conditions(data, line, spaces, check);
	second_conditions(data, line, spaces, check);
	free(line);
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
				check_element(spaces, check, data, line);
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
		ft_error(UNEXPECTED_FLOW, "INVALID MAP IDENTIFIERS\n");
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
