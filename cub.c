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

// int	main(int ac, char **av)
// {
// 	t_mlx_data mlx_data;
// 	t_map_data map_data;

// 	map_data.map_name = av[1];
// 	check_basic_requirements(ac, av);
// 	init(&mlx_data, &map_data);
// 	fill_map(&map_data, &mlx_data);
// 	check_all_the_map(map_data);
// 	init_mlx(&mlx_data);
// 	mlx_data.map = map_data.map;
// 	render(&mlx_data);
// 	mlx_data.map_img->img = mlx_new_image(mlx_data.mlx_ptr, 300,
// 					195);
// 	mlx_data.map_img->addr = mlx_get_data_addr(mlx_data.map_img->img ,
// 				&mlx_data.map_img->bits_per_pixel, &mlx_data.map_img->line_size, &mlx_data.map_img->endian);
// 	draw_map(&mlx_data);
// 	draw_player_of_map(&mlx_data);
// 	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.window, mlx_data.map_img->img,WINDOW_WIDTH - 300,WINDOW_HEIGHT - 200);
// 	//show_map_data(map_data);
// 	mlx_hook(mlx_data.window, KEYPRESS, KEYPRESSMASK, hook_into_key_events, &mlx_data);
// 	mlx_hook(mlx_data.window, KEYRELEASE, KEYRELEASEMASK, rotate_player, &mlx_data);
// 	mlx_hook(mlx_data.window, 17, 0, ft_close, &mlx_data); 
// 	mlx_loop(mlx_data.mlx_ptr);
// }

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void init_window(t_mlx_data *data){

	data->mlx_ptr = mlx_init();
	data->window = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	data->main_img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->main_img.addr = mlx_get_data_addr(data->main_img.img, &data->main_img.bits_per_pixel, &data->main_img.line_size, &data->main_img.endian);
}

int process_input(int keycode, t_mlx_data *data) {
	
	if (keycode == ESC) {
		exit(EXIT_SUCCESS);
	}
	else if (keycode == UP) {
		// move player forward
	}
	else if (keycode == BOTTOM) {
		// move player backward
	}
	else if (keycode == LEFT) {
		// turn the player left
	}
	else if (keycode == RIGHT) {
		// turn the player right
	}
	return (0);
}

void draw_rectangle(t_mlx_data *data, float start_x, float start_y, int flag) {
	float i;
	float j;

	j = start_x;
	i = start_y;
	while (j < start_x + data->square_width - 1)
	{
		i = start_y;
		while (i < start_y + data->square_height - 1){
			if (flag == 1)
				my_mlx_pixel_put(&data->main_img, j, i, 0xFFF000);
			else
				my_mlx_pixel_put(data->map_img, j, i, 0xFFF000);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->main_img.img, 0, 0);
}

void setup(t_mlx_data *data) {
	// init and setup 
	data->player.x = WINDOW_WIDTH / 2;
	data->player.y = WINDOW_HEIGHT / 2;
	data->player.height = 5;
	data->player.width = 5;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.rotation_angle = PI / 2;
	data->square_height = 5;
	data->square_width = 5;
	data->square_height = TILE_SIZE;
	data->square_width = TILE_SIZE;
}

void render_map(t_mlx_data *data)  {
	int x;
	int y;

	y = 0;
	data->square_height *= SCALE;
	data->square_width *= SCALE;
	while (y < WINDOW_HEIGHT){
		x = 0;
		while (x < WINDOW_WIDTH) {
			if (map[(int) y / TILE_SIZE][(int) x / TILE_SIZE] == 1)
				draw_rectangle(data, x * SCALE, y * SCALE, 1);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}
void ft_render(t_mlx_data *data) 
{
	// render every thing
	render_map(data);
	// render_player();
	// render_rays();
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->main_img.img, 0, 0);
}

int main() {

	t_mlx_data data;
	init_window(&data);
	setup(&data);
	ft_render(&data);
	// update(&data);
	mlx_hook(data.window, KEYPRESS, KEYPRESSMASK, process_input, &data);
	mlx_hook(data.window, KEYRELEASE, KEYRELEASEMASK, process_input, &data);
	mlx_loop(data.mlx_ptr);
}