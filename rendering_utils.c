/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:41:27 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 12:14:10 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

// extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];
const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void render(t_mlx_data *data) {
	// TODO:
		// RENDER ALL THE GAME OBJECTS FOR THE CURRENT FRAME
	int x = 0;
	int y  = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0xFF0FFF);
			x+=1;
		}
		y+=1;
	}
	x = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while(x < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0x00F000);
			x += 1;
		}
		y += 1;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
	// ft_draw_player(data);
	// draw_map(data);
	// cast_rays_toward_player_fov(data);
	
}

void ft_drawsquare(t_mlx_data *data, float x, float y)
{
	int i;
	int j;

	i = x;
	while (i < x + data->rays.width)
	{
		j = y;
		while (j < y + data->rays.height)
		{
			my_mlx_pixel_put(data, i, j, 0xFF00FF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
}


void	cast_rays_toward_player_fov(t_mlx_data *data)
{
	float start_angle;
	float target_x;
	float target_y;
	float wall_height;

	int x;
	int y;
	start_angle = data->player.rotation_angle - HALF_FOV;
	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		for (int depth = 0; depth < WINDOW_WIDTH; depth++)
		{
			target_x = data->player.x - sin(start_angle) * depth;
			target_y = data->player.y + cos(start_angle) * depth;
			x = target_x / TILE_SIZE;
			y = target_y / TILE_SIZE;
			if (map[y][x] == 1)
			{
				wall_height = 21000 / (depth + 0.0001);
				data->rays.height = wall_height;
				data->rays.width = SCALE;
				printf("%f %f\n", (WINDOW_HEIGHT / 1.0) + ray * SCALE, (WINDOW_HEIGHT / 2) - wall_height / 2);
				ddaline(data->player.x, data->player.y,
					(WINDOW_HEIGHT / 1.0 + ray * SCALE),
					((WINDOW_HEIGHT / 2) - wall_height / 2),
					data, 0xFF0FFF);
				// ddaline(data->player.x, data->player.y, target_x, target_y, data, 0xFF00FF);
				break ;
			}
			
		}
		start_angle += STEP_ANGLE;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
}

void draw_map(t_mlx_data *data)
{
	int	i;
	int j;
	float x;
	float y;
	t_vector *borders; 

	borders = malloc(sizeof(t_vector));
	borders->x = -1;
	borders->y = -1;
	borders->next = NULL;
	x = 0;
	y = 0;
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		x = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 1)
			{
				t_vector *temp = malloc(sizeof(t_vector));
				temp->x = x;
				temp->y = y;
				temp->next = NULL;
				lstadd_front(&borders, temp);
				drawsquare(data, x, y);
			}
			x += 64;
			j++;
		}
		i++;
		y += 64 ;
	}
	data->borders = borders;
}

void drawsquare(t_mlx_data *data, int x, int y)
{
	int i;
	int j;

	i = x;
	while (i < x + TILE_SIZE)
	{
		j = y;
		while (j < y + TILE_SIZE)
		{
			my_mlx_pixel_put(data, i, j, 0x808080);
			j++;
		}
		i++;
	}
}


void ft_draw_player(t_mlx_data *data)
{
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle) * 50,
		data->player.y + cos(data->player.rotation_angle) * 50,
		data, 0xFF0000
	);
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle - HALF_FOV) * 50,
		data->player.y + cos(data->player.rotation_angle - HALF_FOV) * 50,
		data, 0xFF0000
	);
	ddaline(
		data->player.x, data->player.y,
		data->player.x - sin(data->player.rotation_angle + HALF_FOV) * 50,
		data->player.y + cos(data->player.rotation_angle + HALF_FOV) * 50,
		data, 0xFF0000
	);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->img, 0, 0);
}