/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/12 11:51:10 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "mlx.h"
# include "Libft/libft.h"
# include <float.h>

# define MAIN_MAP 1
# define MINI_MAP 0

# define RIGHT 124
# define ESC 53
# define LEFT 123
# define UP 126
# define BOTTOM 125
# define PI 3.14159265
# define TWO_PI 6.28318530
# define E  1.57079632679
# define S  PI
# define W 4.71238898038
# define N  0

# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2

# define FUNCTION_FAILED 2
# define UNEXPECTED_FLOW 1

# define KEYRELEASE 3
# define KEYPRESSMASK 1L
# define KEYPRESS 2
# define KEYRELEASEMASK 2L

# define MOVE_STEP 12
# define TURN_SPEED 0.1
# define FOV 1.0472
# define HALF_FOV 30
# define SCALE 0.2
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000

typedef struct n_u
{
	float	prep_distance;
	int		ofsetx;
	float	distance_proj_plan;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	char	*dst;
	int		e;
	int		distance;
	int		ofsety;
}t_numb_u;

typedef struct raycast_s {
	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	int		found_horz_wall_hit;
	int		horz_wall_content;
	int		flag;
	int		temp_x;
	int		temp_y;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	horz_wall_hit_x;
	float	horz_wall_hit_y;
	float	next_horz_touch_x;
	float	next_horz_touch_y;
	float	x_to_check;
	float	y_to_check;
	int		found_ver_wall_hit;
	float	ver_wall_hit_x;
	float	ver_wall_hit_y;
	int		ver_wall_content;
	float	next_ver_touch_x;
	float	next_ver_touch_y;
	float	horz_hit_distance;
	float	ver_hit_distance;
}t_raycast;

typedef struct img_data{
	void		*img;
	char		*addr;
	char		*addr_map;
	int			x;
	int			y;
	int			endian;
	int			bits_per_pixel;
	int			line_size;
}t_img;

typedef struct s_line {
	float		x;
	float		y;
	float		x1;
	float		y1;
	int			flag;
	int			color;
	float		len;
	int			dx;
	int			dy;
	float		sx;
	float		sy;
	float		xinc;
	float		yinc;
	int			h;
}t_line;

typedef struct s_rays {
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	bool	was_hit_vertical;
	bool	is_ray_facing_up;
	bool	is_ray_facing_left;
	bool	is_ray_facing_right;
	bool	is_ray_facing_down;
	int		wall_hit_content;
}t_rays;

typedef struct s_mini_map {
	int		width;
	int		height;
	int		tile_size;
	t_img	map_img;
}t_mini_map;

typedef struct s_player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
}t_player;

typedef struct map_data {
	char	**map;
	char	*map_name;
	int		map_lines;
	char	*north_texture;
	char	*south_texture;
	char	*west_textrure;
	char	*east_texture;
	int		longest_line;
	int		floor_color[3];
	int		ceilling_color[3];
}t_map_data;

typedef struct s_square
{
	float	start_x;
	float	start_y;
	int		color;
	int		width;
	int		height;
}t_square;

typedef struct img_with_direction
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
}t_dir_img;

typedef struct mlx_data {
	t_player	player;
	t_map_data	map_data;
	t_img		main_img;
	t_rays		*rays;
	int			tile_size;
	int			window_width;
	int			window_height;
	int			square_height;
	int			square_width;
	void		*mlx_ptr;
	void		*window;
}t_mlx_data;

typedef struct fix_map
{
	char	*line_of_map;
	int		len;
}t_fix_map;

void		ddaline(t_line line, t_mlx_data *data);
void		check_basic_requirements(int ac, char **av);
void		map_data_constructor(t_map_data *map_data);
void		free_grid(char **grid);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		skip_empty_lines(char **grid, int *n, int map_len);
void		check_map_texture(t_map_data map_data);
void		call_check_zeros(t_fix_map *map, int len);
void		check_the_zeros(t_fix_map *map, int i, int j, int len);
void		fill_map(t_mlx_data *data);
void		fill_rgb_array(char *line, int *arr);
void		update(t_mlx_data *data);
void		get_player_pos(t_mlx_data *data);
void		check_all_the_map(t_map_data *map_data);

int			check_file_extention(char *file);
int			check_char(char c);
int			count_spaces(char *line);
int			ft_error(int exit_code, char *fatal);
int			count_map_lines(char *map_name);
int			ft_close(t_mlx_data *data);
int			fill_map_data(char **grid, t_mlx_data *data);
int			ft_render(t_mlx_data *data);

char		**convert_file_to_grid(t_mlx_data *data);

bool		get_texture_path(char *l, t_mlx_data *data);
bool		is_number(char *s);
bool		is_valid_line(char *line);

float		get_player_dir(char c);
t_map_data	parse_map(char *map_name);

#endif
