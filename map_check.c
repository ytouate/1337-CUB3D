/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:09:24 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/30 11:08:14 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_map_borders(t_map_data map_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_data.map[i])
	{
		j = 0;
		char *temp = ft_strtrim(map_data.map[i], "\t ");
		if (temp[j] != '1')
			ft_error(1, "Map must be surrounded by walls\n");
		while (map_data.map[i][j])
		{
			j++;
		}
		i++;
	}
	return (0);
}