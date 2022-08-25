/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:03:36 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/25 13:03:38 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	s[j] = '\0';
	while (str[j])
	{
		if (str[j] != ' ')
			ft_error(UNEXPECTED_FLOW, "INVALID TEXTURE PATH\n");
		j++;
	}
	free(str);
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
			ft_error(UNEXPECTED_FLOW, "DUPLICATED TEXTURES\n");
		check[6] += 1;
		data->map_data.north_texture = fill_the_path(line + spaces);
	}
	else if (!ft_strncmp("SO ", line + spaces, 3))
	{
		check[1] += 1;
		if (check[1] > 1)
			ft_error(UNEXPECTED_FLOW, "DUPLICATED TEXTURES\n");
		check[6] += 1;
		data->map_data.south_texture = fill_the_path(line + spaces);
	}
	else if (!ft_strncmp("WE ", line + spaces, 3))
	{
		check[2] += 1;
		if (check[2] > 1)
			ft_error(UNEXPECTED_FLOW, "DUPLICATED TEXTURES\n");
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
			ft_error(UNEXPECTED_FLOW, "DUPLICATED TEXTURES\n");
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
		ft_error(UNEXPECTED_FLOW, "INVALID MAP IDENTIFIERS\n");
}
