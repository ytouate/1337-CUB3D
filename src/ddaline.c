/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:38:26 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/11 11:21:51 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ddaline(t_line line, t_mlx_data *data)
{
	line.dx = line.x1 - line.x;
	line.dy = line.y1 - line.y;
	line.h = 0;
	if (abs(line.dx) > abs(line.dy))
		line.len = abs(line.dx);
	else
		line.len = abs(line.dy);
	line.xinc = line.dx / line.len;
	line.yinc = line.dy / line.len;
	while (line.h <= line.len)
	{
		line.sx = line.x + line.xinc * line.h;
		line.sy = line.y + line.yinc * line.h;
		line.h++;
		if (line.sx > 0 && line.sx < 1920 && line.sy > 0 && line.sy < 1080)
		{
			if (line.flag == MAIN_MAP)
				my_mlx_pixel_put(&data->main_img, line.sx, line.sy, line.color);
		}
	}
}
