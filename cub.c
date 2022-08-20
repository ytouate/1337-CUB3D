/*                                                                            */
/* ************************************************************************** */
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
	data->map_img = malloc(sizeof(t_img));
	data->map_img->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH * SCALE ,WINDOW_HEIGHT * SCALE);
	data->map_img->addr = mlx_get_data_addr(data->map_img->img, &data->map_img->bits_per_pixel, &data->map_img->line_size, &data->map_img->endian);
	data->main_img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->main_img.addr = mlx_get_data_addr(data->main_img.img, &data->main_img.bits_per_pixel, &data->main_img.line_size, &data->main_img.endian);
}

void rotate_player(t_mlx_data *data) {
	data->player.rotation_angle += data->player.turn_direction * 0.1;
	update(data);
	ft_render(data);
}

bool map_has_wall_at(float x, float y) {
	int x_index;
	int y_index;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 ||  y > WINDOW_HEIGHT) {
		return (true);
	}
	x_index = floor(x / TILE_SIZE);
	y_index = floor(y / TILE_SIZE);
	return (map[y_index][x_index] != 0);
}

void move_player(t_mlx_data *data) {
	float new_x;
	float new_y;
	float move_step;

	
	move_step = data->player.walk_direction * 8;
	new_x = data->player.x + cos(data->player.rotation_angle) * move_step;
	new_y = data->player.y + sin(data->player.rotation_angle) * move_step;
	
	if (!map_has_wall_at(new_x, new_y))
	{
		update(data);
		data->player.x = new_x;
		data->player.y = new_y;
		
	}
	ft_render(data);
}

int process_input(int keycode, t_mlx_data *data) {
	
	
	if (keycode == ESC) {
		exit(EXIT_SUCCESS);
	}
	else if (keycode == UP) {
		// move player forward
		data->player.walk_direction = +1;
		move_player(data);
	}
	else if (keycode == BOTTOM) {
		// move player backward
		data->player.walk_direction = -1;
		move_player(data);
	}
	else if (keycode == LEFT) {
		// turn the player left
		data->player.turn_direction = -1;
		// move_player(data);
		rotate_player(data);
	}
	else if (keycode == RIGHT) {
		// turn the player right
		data->player.turn_direction = +1;
		// move_player(data);
		rotate_player(data);
	}
	return (0);
}

void draw_rectangle(t_mlx_data *data, float start_x, float start_y, int flag, int color, int width, int height) {
	float i;
	float j;

	j = start_x;
	i = start_y;
	while (j < start_x + width)
	{
		i = start_y;
		while (i < start_y + height) {
			if (flag == MAIN_MAP)
				my_mlx_pixel_put(&data->main_img, j, i, color);
			else
				my_mlx_pixel_put(data->map_img, j, i, color);
			i++;
		}
		j++;
	}
	// mlx_put_image_to_window(data->mlx_ptr, data->window, data->main_img.img, 0, 0);
}

void setup(t_mlx_data *data) {
	// init and setup 
	data->color_buffer = NULL;
	data->color_buffer = malloc(sizeof(uint32_t) * (WINDOW_HEIGHT * WINDOW_WIDTH));
	if (data->color_buffer == NULL)
		ft_error(FUNCTION_FAILED, "malloc failed in setup() \n");
	data->player.x = WINDOW_WIDTH / 2;
	data->player.y = WINDOW_HEIGHT / 2;
	data->player.height = 1;
	data->player.width = 1;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.rotation_angle = PI / 2;
}

void render_rays(t_mlx_data *data)  {
	for (int i = 0; i < NUM_RAYS; i++) {
		ddaline(
			SCALE * data->player.x,
			SCALE * data->player.y,
			SCALE * data->rays[i].wall_hit_x,
			SCALE * data->rays[i].wall_hit_y,
			data,
			0xFF0000
		);
	}
}

void render_map(t_mlx_data *data)  {
	int x;
	int y;

	y = 0;

	while (y < WINDOW_HEIGHT){
		x = 0;
		while (x < WINDOW_WIDTH) {
			if (map[(int) y / TILE_SIZE][(int) x / TILE_SIZE] == 1)
				draw_rectangle(
					data,
					x * SCALE,
					y * SCALE,
					MINI_MAP,
					0x00FF00,
					TILE_SIZE * SCALE,
					TILE_SIZE * SCALE
				);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
}

void render_player(t_mlx_data *data) {
	data->square_height = 1;
	data->square_width = 1;
	draw_rectangle(
		data,
		SCALE * data->player.x,
		SCALE * data->player.y,
		MINI_MAP,
		0xFF0000,
		1 * SCALE,
		1 * SCALE
	);
	ddaline (
		SCALE * data->player.x,
		SCALE * data->player.y,
		SCALE * (data->player.x + cos(data->player.rotation_angle) * 40),
		SCALE * (data->player.y + sin(data->player.rotation_angle) * 40),
		data,
		0xFF0000
	);
}

float normalize_angle(float angle) {
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float distance_between_points(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_ray(t_mlx_data *data, float rayAngle, int stripId) {
    rayAngle = normalize_angle(rayAngle);
    
    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = false;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = data->player.x + (yintercept - data->player.y) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (map_has_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = false;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = data->player.y + (xintercept - data->player.x) * tan(rayAngle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;
    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (map_has_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = foundHorzWallHit
        ? distance_between_points(data->player.x, data->player.y, horzWallHitX, horzWallHitY)
        : FLT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distance_between_points(data->player.x, data->player.y, vertWallHitX, vertWallHitY)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) {
        data->rays[stripId].distance = vertHitDistance;
        data->rays[stripId].wall_hit_x = vertWallHitX;
        data->rays[stripId].wall_hit_y = vertWallHitY;
        data->rays[stripId].wall_hit_content = vertWallContent;
        data->rays[stripId].was_hit_vertical = true;
    } else {
        data->rays[stripId].distance = horzHitDistance;
        data->rays[stripId].wall_hit_x = horzWallHitX;
        data->rays[stripId].wall_hit_y = horzWallHitY;
        data->rays[stripId].wall_hit_content = horzWallContent;
        data->rays[stripId].was_hit_vertical = false;
    }
    data->rays[stripId].ray_angle = rayAngle;
    data->rays[stripId].is_ray_facing_down = isRayFacingDown;
    data->rays[stripId].is_ray_facing_up = isRayFacingUp;
    data->rays[stripId].is_ray_facing_left = isRayFacingLeft;
    data->rays[stripId].is_ray_facing_right = isRayFacingRight;
}
	
void cast_all_rays(t_mlx_data *data) {
	float ray_angle = data->player.rotation_angle - (FOV / 2);

	for (int strip_id = 0; strip_id < NUM_RAYS; strip_id++) {
		cast_ray(data, ray_angle, strip_id);
		ray_angle += (FOV / NUM_RAYS);
	}
}


void clear_color_buffer(t_mlx_data *data, uint32_t color) {
	for (int x = 0; x < WINDOW_WIDTH; x++){
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			data->color_buffer[(WINDOW_WIDTH * y) + x] = color;
		}
	}
}

void generate_3d_projection(t_mlx_data *data) {
	for (int i = 0; i < NUM_RAYS; i++) {
		float prep_distance = data->rays[i].distance * cos(data->rays[i].ray_angle - data->player.rotation_angle) ;
		float distance_proj_plan = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		float projected_wall_height = (TILE_SIZE / prep_distance) * distance_proj_plan;
		int wall_strip_height = (int)projected_wall_height;
		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0) {
			wall_top_pixel = 0;
		}
		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > WINDOW_HEIGHT)  {
			wall_bottom_pixel = WINDOW_HEIGHT;
		}
		for (int j = wall_top_pixel; j < wall_bottom_pixel; j++) {
			if (data->rays[i].was_hit_vertical)
				my_mlx_pixel_put(&data->main_img, i, j, 0xFFFFFF);
			else
				my_mlx_pixel_put(&data->main_img, i, j, 0xFFCCCC);
		}
	}

}

void render_ceiling_and_floor(t_mlx_data *data) {

	int i;
	for (i = 0; i < WINDOW_HEIGHT / 2; i++) {
		for (int j = 0; j < WINDOW_WIDTH; j++) {
			my_mlx_pixel_put(&data->main_img, j, i, 0xD3D3D3);
		}
	}
	for (int k = i; k < WINDOW_HEIGHT; k++) {
		for (int j = 0; j < WINDOW_WIDTH; j++) {
			my_mlx_pixel_put(&data->main_img, j, k, 0xb3b1b4);
		}
	}
}
void ft_render(t_mlx_data *data) 
{
	// render everything
	// clear the color buffer
	cast_all_rays(data);
	// render_map(data);
	// render_rays(data);
	// render_player(data);
	render_ceiling_and_floor(data);
	generate_3d_projection(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->map_img->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->main_img.img, 0, 0);
}

int reset(int keycode, t_mlx_data *data) {
	if (keycode == UP) {
		// move player forward
		data->player.walk_direction = 0;
	}
	else if (keycode == BOTTOM) {
		// move player backward
		data->player.walk_direction = 0;
	}
	else if (keycode == LEFT) {
		// turn the player left
		data->player.turn_direction = 0;
	}
	else if (keycode == RIGHT) {
		// turn the player right
		data->player.turn_direction = 0;
	}
	return (0);
}

void update(t_mlx_data *data) {

	mlx_clear_window(data->mlx_ptr, data->window);
	data->main_img.img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->main_img.addr = mlx_get_data_addr(data->main_img.img, &data->main_img.bits_per_pixel, &data->main_img.line_size, &data->main_img.endian);
	// cast_all_rays(data);
}

void map_setup(t_mlx_data *data)
{
	fill_map(data);
}
int main(int ac, char **av) {

	t_mlx_data data;

	check_basic_requirements(ac, av);
	init_window(&data);
	setup(&data);
	ft_render(&data);
	mlx_hook(data.window, KEYPRESS, KEYPRESSMASK, process_input, &data);
	mlx_hook(data.window, KEYRELEASE, KEYRELEASEMASK, reset, &data);
	mlx_loop(data.mlx_ptr);
}