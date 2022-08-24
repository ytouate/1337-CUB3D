/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:43:57 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 10:44:45 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		ft_error(6, "INVALID MAP\n");
	if (j > map[i - 1].len || j > map[i + 1].len)
		ft_error(7, "INVALID MAP\n");
	if (map[i].line_of_map[j + 1] == ' ' || map[i].line_of_map[j - 1] == ' ' )
		ft_error(8, "INVALID MAP\n");
	if (map[i - 1].line_of_map[j] == ' ' || map[i + 1].line_of_map[j] == ' ' )
		ft_error(9, "INVALID MAP\n");
}
//check the flag

void	check_flag(int flag)
{
	if (flag != 1)
		ft_error(5, "INVALID MAP\n");
}
// checks if the map is surrounded by zeros;

void	call_check_zeros(t_fix_map *map, int len)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (i < len)
	{
		j = 0;
		if (map[i].len == 0 && i < len - 1 && map[i + 1].len > 0)
			ft_error(3, "INVALID MAP\n");
		while (map[i].line_of_map[j])
		{
			if (check_char(map[i].line_of_map[j]) == 0)
				ft_error(4, "INVALID MAP\n");
			if (map[i].line_of_map[j] == '0'
				|| ft_isalpha(map[i].line_of_map[j]))
				check_the_zeros(map, i, j, len);
			if (ft_isalpha(map[i].line_of_map[j]))
				flag += 1;
			j++;
		}
		i++;
	}
	check_flag(flag);
}

//this function for fill the map with lens
void	check_all_the_map(t_map_data *map_data)
{
	t_fix_map	*map_with_len;
	int			i;

	map_data->longest_line = 0;
	i = 0;
	map_with_len = malloc(sizeof(t_fix_map) * map_data->map_lines);
	while (map_data->map[i])
	{
		map_with_len[i].len = ft_strlen(map_data->map[i]);
		if (map_with_len[i].len > map_data->longest_line)
			map_data->longest_line = map_with_len[i].len;
		map_with_len[i].line_of_map = map_data->map[i];
		i++;
	}
	call_check_zeros(map_with_len, map_data->map_lines);
}
