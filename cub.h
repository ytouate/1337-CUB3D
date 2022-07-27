/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:19:16 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/27 12:33:11 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
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

enum {
	RIGHT 	= 124,
	ESC 	= 53,
	LEFT 	= 123,
	UP 		= 126,
	BOTTOM 	= 125
};

int	ft_error(int exit_code, char *fatal);

#endif