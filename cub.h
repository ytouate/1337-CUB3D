/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/31 19:53:21 by ytouate          ###   ########.fr       */
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

typedef struct mlx_data {
	void	*mlx_ptr;
	void	*window;
	int		window_x_size;
	int		window_y_size;
}t_mlx_data;


typedef struct map_data {
	char 	**map;
	int		map_lines;
	char	*north_texture;
	char	*south_texture;
	char	*west_textrure;
	char	*east_texture;
	int		floor_color[3];
	int		ceilling_color[3];
}t_map_data;

enum {
	RIGHT 	= 124,
	ESC 	= 53,
	LEFT 	= 123,
	UP 		= 126,
	BOTTOM 	= 125
};

t_map_data	parse_map(char *map_name);
int			ft_error(int exit_code, char *fatal);
int			count_map_lines(char *map_name);
char		**convert_file_to_grid(char *file_name, int file_size);
bool		get_texture_path(char *l, t_map_data *map_data);
void		check_map_texture(t_map_data map_data);
int			check_map_borders(t_map_data map_data);
bool	got_overflowed(int *rgb);
#endif