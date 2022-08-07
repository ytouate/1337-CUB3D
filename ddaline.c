/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:38:26 by ilefhail          #+#    #+#             */
/*   Updated: 2022/08/06 15:28:40 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ddaline(int x,int y, int x1, int y1, t_mlx_data img)
{
	float	len; 
	int		dx;
	int		dy;
	float 	sx;
	float 	sy;
	float	xinc;
	float	yinc;
	int h;

	dx = x1 - x;
	dy = y1 - y;
	h = 0;
	if (abs(dx) > abs(dy))
		len = abs(dx);
	else
		len = abs(dy);
	xinc = dx / len;
	yinc = dy / len;
	while (h <= len)
	{
		sx = x + xinc * h;
		sy = y + yinc * h;
		h++;
		if (sx > 0 && sx < 1920 && sy > 0 && sy < 1080)
			my_mlx_pixel_put(&img, sx, sy, 0x008000);
	}
}

