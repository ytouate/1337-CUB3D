/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/12 12:33:30 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	lstadd_front(t_vector **lst, t_vector *new)
{
	new ->next = *lst;
	*lst = new;
}

double	get_player_dir(char	c)
{
	if (c == 'N')
		return (N);
	else if (c == 'E')
		return (E);
	else if (c == 'W')
		return (W);
	else if (c == 'S')
		return (S);
	return (0);
}

bool got_collided(t_mlx_data *data)
{
	while (data->borders)
	{
		if ((data->borders->x > data->player.x || data->borders->y < data->player.x)
			&& data->borders->y == data->player.y)
			return (true);
		data->borders = data->borders->next;
	}
	return (false);
}
void	free_grid(char **grid)
{
	int i;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

void print_grid(char **s){
	int i = 0;
	while (s[i])
		printf("%s\n", s[i++]);
}

void show_map_data(t_map_data map_data)
{
	printf("======================the map======================\n");
	print_grid(map_data.map);
	printf("the textures\n");
	printf("%s\n", map_data.north_texture);
	printf("%s\n", map_data.south_texture);
	printf("%s\n", map_data.west_textrure);
	printf("%s\n", map_data.east_texture);
	printf("the floor colors\n");
	for (int i = 0; i < 3; i++)
		printf("%d\t", map_data.floor_color[i]);
	printf("\n");
	printf("the ceiling colors\n");
	for (int i = 0; i < 3; i++)
		printf("%d\t", map_data.ceilling_color[i]);
	printf("\n");
}

void	draw_player_of_map(t_mlx_data *data)
{
	float	x;
	float	y;
	float	i;
	float	j;

	x = (300 * data->player.x) / WINDOW_WIDTH;
	y = (195 * data->player.y) / WINDOW_HEIGHT;
	i = x;
	while (i < x + 5)
	{
		j = y;
		while (j < y + 5)
		{
			my_mlx_pixel_put(data->map_img, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_mlx_data mlx_data;
	t_map_data map_data;

	map_data.map_name = av[1];
	check_basic_requirements(ac, av);
	init(&mlx_data, &map_data);
	fill_map(&map_data, &mlx_data);
	check_all_the_map(map_data);
	mlx_data.main_img = malloc(sizeof(t_img));
	mlx_data.map_img = malloc(sizeof(t_img));
	init_mlx(&mlx_data);
	mlx_data.map = map_data.map;
	render(&mlx_data);
	mlx_data.map_img->img = mlx_new_image(mlx_data.mlx_ptr, 300,
					195);
	mlx_data.map_img->addr = mlx_get_data_addr(mlx_data.map_img->img ,
				&mlx_data.map_img->bits_per_pixel, &mlx_data.map_img->line_size, &mlx_data.map_img->endian);
	draw_map(&mlx_data);
	draw_player_of_map(&mlx_data);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.window, mlx_data.map_img->img,WINDOW_WIDTH - 300,WINDOW_HEIGHT - 200);
	//show_map_data(map_data);
	mlx_hook(mlx_data.window, KEYPRESS, KEYPRESSMASK, hook_into_key_events, &mlx_data);
	mlx_hook(mlx_data.window, KEYRELEASE, KEYRELEASEMASK, rotate_player, &mlx_data);
	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data); 
	mlx_loop(mlx_data.mlx_ptr);
}
