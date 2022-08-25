/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:45:02 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/11 16:46:12 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub.h"

int		ft_close(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->window);
	// free resources;
	exit(EXIT_SUCCESS);
	return (0);
}
