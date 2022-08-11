/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:46:19 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 10:46:52 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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