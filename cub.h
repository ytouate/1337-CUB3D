/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 11:25:03 by ytouate          ###   ########.fr       */
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

# define E  PI / 2
# define S  PI
# define W  3 * PI/2
# define N  0 * PI

# define A_KEY 0
# define W_KEY 13
# define S_KEY 1
# define D_KEY 2

# define PI 3.141592653589793
# define TWO_PI 6.28318530

#define FUNCTION_FAILED 2
#define UNEXPECTED_FLOW 1

# define KEYRELEASE 3
# define KEYPRESSMASK 1L
# define KEYPRESS 2
# define KEYRELEASEMASK 2L

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV (60 * (PI / 180.0))
# define HALF_FOV FOV / 2

# define NUM_RAYS WINDOW_WIDTH
# define STEP_ANGLE FOV / NUM_RAYS

typedef struct s_vector
{
	int				x;
	int				y;
	struct s_vector	*next;
}t_vector;

typedef struct s_rays {
	double	step_angle;
	double	width;
	double	height;
	double	start_angle;
}t_rays;

typedef struct s_player {
	float	x;
	float	y;
	int		turn_direction; // -1 for left +1 for right;
	int		walk_direction; // -1 for back, +1 for fron
	float	rotation_angle;
}t_player;

typedef struct mlx_data {
	t_vector	*borders;
	t_player	player;
	t_rays		rays;
	void		*mlx_ptr;
	void		*window;
	void		*img;
	char		*addr;
	char		**map;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}t_mlx_data;

typedef struct map_data {
	char 	**map;
	char	*map_name;
	int		map_lines;
	char	*north_texture;
	char	*south_texture;
	char	*west_textrure;
	char	*east_texture;
	int		floor_color[3];
	int		ceilling_color[3];
}t_map_data;

typedef struct fix_map
{
	char	*line_of_map;
	int		len;
}t_fix_map;

enum {
	RIGHT 	= 124,
	ESC 	= 53,
	LEFT 	= 123,
	UP 		= 126,
	BOTTOM 	= 125,
};
void	cast_rays_toward_player_fov(t_mlx_data *data);
void	lstadd_front(t_vector **lst, t_vector *new);
bool got_collided(t_mlx_data *data);
void	check_basic_requirements(int ac, char **av);
void	map_data_constructor(t_map_data *map_data);
void show_map_data(t_map_data map_data);
void	free_grid(char **grid);
void	ddaline(float x, float y, float x1, float y1, t_mlx_data *data, int color);
int	ft_error(int exit_code, char *fatal);
void update_window(t_mlx_data *data);
void init_mlx(t_mlx_data *mlx_data);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int count_map_lines(char *map_name);
bool	get_map_rgb(char *line, t_map_data *map_data);
bool	got_overflowed(int *rgb);
int		check_file_extention(char *file);
bool	is_valid_line(char *line);
void	check_all_the_map(t_map_data map_data);
void	call_check_zeros(t_fix_map *map, int len);
void	check_the_zeros(t_fix_map *map, int i, int j, int len);
void render(t_mlx_data *data);
int	check_char(char c);
void draw_map(t_mlx_data *data);
void ft_draw_player(t_mlx_data *data);
void drawsquare(t_mlx_data *data, int x, int y);
void	skip_empty_lines(char **grid, int *n, int map_len);
void check_map_texture(t_map_data map_data);
char **convert_file_to_grid(char *file_name, int file_size);
bool	get_texture_path(char *l, t_map_data *map_data);
int count_spaces(char *line);
int		check_map_borders(t_map_data map_data);
int	hook_into_key_events(int keycode, t_mlx_data *data);
int		ft_close(t_mlx_data *data);
int rotate_player(int keycode,t_mlx_data *data);
void init(t_mlx_data *mlx_data, t_map_data *map_data);
void fill_map(t_map_data *map_data, t_mlx_data *mlx_data);
void init_map_data(t_map_data *map_data);
int	fill_map_data(char **grid, t_map_data *map_data);
void	fill_rgb_array(char *line, int *arr);
bool is_number(char *s);
bool	check_map_identifiers(char *line);
void print_grid(char **s);
double	get_player_dir(char	c);
int			count_spaces(char *line);
int			ft_error(int exit_code, char *fatal);
int			count_map_lines(char *map_name);
int			check_map_borders(t_map_data map_data);
char		**convert_file_to_grid(char *file_name, int file_size);
bool		got_overflowed(int *rgb);
bool		get_texture_path(char *l, t_map_data *map_data);
bool		is_valid_line(char *line);
void		check_map_texture(t_map_data map_data);
t_map_data	parse_map(char *map_name);
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
void draw_map(t_mlx_data *data);
void draw_player(float x, float y, t_mlx_data *data);
void render(t_mlx_data *data);
#endif