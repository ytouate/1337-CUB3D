/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/05 15:18:36 by ytouate          ###   ########.fr       */
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

typedef struct s_vector
{
	int	x;
	int y;
	struct s_vector	*next;
}t_vector;

typedef struct s_player {
	int player_pos[2];
	int player_viewer_height; // the player is half the walls height which is 64 so 32 unit in my case;
	int player_fov; // must of human have a fov of 90 we sit the fov 60
	int projection_plane[2]; // projection plane dimension
	int player_dir; // the player direction represented by an angle
}t_player;

typedef struct mlx_data {
	void	*mlx_ptr;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		window_x_size;
	int		window_y_size;
	t_vector *borders;
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	char	**map;
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
	E = 90,
	S = 180,
	W = 270,
	N =	260
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


#endif