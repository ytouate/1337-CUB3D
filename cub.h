/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/08 15:15:46 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define PI 3.141592653589793
#define FUNCTION_FAILED 2
#define UNEXPECTED_FLOW 1
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
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1L
# define KEYRELEASEMASK 2L
# define FOV 60 * (PI / 180.0)
# define HALF_FOV FOV / 2
# define NUM_RAYS 320
# define STEP_ANGLE FOV / NUM_RAYS

typedef struct s_vector
{
	int				x;
	int				y;
	struct s_vector	*next;
}t_vector;


typedef struct s_rays {
	double	step_angle;
	double	casted_rays;
	double	start_angle;
	double	max_depth;
}t_rays;

typedef struct s_player {
	double	player_pos[2];
	double	player_dir;
	double	player_angle;
	int		player_viewer_height;
	int		projection_plane[2];
	int		player_dist;
}t_player;

typedef struct mlx_data {
	t_vector	*borders;
	t_player	*player;
	t_rays		*rays;
	float		angle;
	void		*mlx_ptr;
	void		*window;
	void		*img;
	char		*addr;
	char		**map;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int			window_x_size;
	int			window_y_size;
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
void	ddaline(int x,int y, int x1, int y1, t_mlx_data img, int color);
void draw_map(t_mlx_data *data);
void draw_player(float x, float y, t_mlx_data *data);
#endif