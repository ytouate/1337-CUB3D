/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:38:26 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/01 12:00:44 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ddaline(t_x_y put, int x1, int y1, t_mlx_data img)
{
	float	len;
	t_x_y	d;
	float	xinc;
	float	yinc;

	d.sx = x1 - put.x;
	d.sy = y1 - put.y;
	d.h = 0;
	if (abs(d.sx) > abs(d.sy))
		len = abs(d.sx);
	else
		len = abs(d.sy);
	xinc = d.sx / len;
	yinc = d.sy / len;
	while (d.h <= len)
	{
		d.x = put.x + xinc * d.h;
		d.y = put.y + yinc * d.h;
		d.h++;
		if (d.x > 0 && d.x < 1920 && d.y > 0 && d.y < 1080)
			my_mlx_pixel_put(&img, d.x, d.y, 0x008000);
	}
}

