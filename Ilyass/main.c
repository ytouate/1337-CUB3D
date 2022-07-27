/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:35:50 by ilefhail          #+#    #+#             */
/*   Updated: 2022/07/21 18:35:54 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct t_tringle{
    int x;
    int y;
}           t_tringle;

typedef struct t_l
{
	void	*mlx;
	void	*mlx_win;
	t_tringle h;
	t_data img;
	int **arr;
}t_l;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void  ft_triangle(t_tringle l, t_data *data)
{
	int s = l.x;
	int f;

	while (l.x < s + 10)
	{
		f = l.y;
		while (f < l.y + 10)
		{
			my_mlx_pixel_put(data, l.x, f, 0x00FF0000);
			f++;
		}
		l.x++;
	}
}

void  ft_triangle_map(t_tringle l, t_data *data)
{
	int s = l.x;
	int f;

	while (l.x < s + 40)
	{
		f = l.y;
		while (f < l.y + 40)
		{
			my_mlx_pixel_put(data, l.x, f, 0x008000);
			f++;
		}
		l.x++;
	}
}

void ft_draw_map(int **arr, t_l l)
{
	int i = 0;
	int j = 0;

	l.h.y = 0;
	while (i < 10)
	{
		j = 0;
		l.h.x = 0;
		while (j < 10)
		{
			if (arr[i][j] == 0)
				l.h.x += 40;
			else
			{
				ft_triangle_map(l.h, &l.img);
				l.h.x += 40;
			}
			j++;
		}
		i++;
		l.h.y += 40;
	}
}
void ft_clear_and_put(t_l *l)
{
	t_data img;

	mlx_clear_window(l->mlx, l->mlx_win);
	img.img = mlx_new_image(l->mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_triangle(l->h, &img);
	l->img = img;
	ft_draw_map(l->arr, *l);
	mlx_put_image_to_window(l->mlx, l->mlx_win, img.img, 0, 0);
}

int ft_key(int keyhook, t_l *l)
{
	printf("%d\n",keyhook);
	if (keyhook == 124) // right
	{
		l->h.x += 20;
		ft_clear_and_put(l);
	}
	else if (keyhook == 125) // down
	{
		l->h.y += 20;
		ft_clear_and_put(l);
	}
	else if (keyhook == 126)
	{
		l->h.y -= 20;
		ft_clear_and_put(l);
	}
	else if (keyhook == 123) 
	{
		l->h.x -= 20;
		ft_clear_and_put(l);
	}
	return (0);
}

int	main(void)
{
	t_l l;
	int temp[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
					{1,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,1,1,1},
					{1,0,0,0,0,0,1,0,0,1},
					{1,0,0,0,0,0,1,0,0,1},
					{1,0,0,0,0,0,1,0,0,1},
					{1,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,0,0,1},
					{1,1,1,1,1,1,1,1,1,1},};
	l.arr = malloc(sizeof(int *) * 10);
	for (int i = 0; i < 10; i ++)
	{
		l.arr[i] = malloc(sizeof(int) * 10);
		for (int j = 0; j < 10; j++)
		{
			l.arr[i][j] = temp[i][j];
		}
	}
	l.mlx = mlx_init();
	l.mlx_win = mlx_new_window(l.mlx, 800, 800, "Hello world!");
	l.img.img = mlx_new_image(l.mlx, 800, 800);
	l.img.addr = mlx_get_data_addr(l.img.img, &l.img.bits_per_pixel, &l.img.line_length,
								&l.img.endian);
	ft_draw_map(l.arr, l);
	l.h.x = 5;
    l.h.y = 5;
	ft_triangle(l.h, &l.img);
	mlx_put_image_to_window(l.mlx, l.mlx_win, l.img.img, 0, 0);
	mlx_key_hook(l.mlx_win, ft_key, &l);
	mlx_put_image_to_window(l.mlx, l.mlx_win, l.img.img, 0, 0);
	mlx_loop(l.mlx);
}
