/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:35:22 by ytouate           #+#    #+#             */
/*   Updated: 2022/08/25 15:10:22 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	setup(t_mlx_data *data)
{
	get_player_pos(data);
	data->window_height = data->map_data.map_lines * data->tile_size;
	data->window_width = data->map_data.longest_line * data->tile_size;
	data->rays = malloc(sizeof(t_rays) * WINDOW_WIDTH);
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	data.tile_size = 64;
	check_basic_requirements(ac, av);
	data.map_data.map_name = av[1];
	map_setup(&data);
	setup(&data);
	init_window(&data);
	ft_render(&data);
	mlx_hook(data.window, 17, 0, ft_close, &data);
	mlx_hook(data.window, KEYPRESS, KEYPRESSMASK, process_input, &data);
	mlx_hook(data.window, KEYRELEASE, KEYRELEASEMASK, reset, &data);
	mlx_loop_hook(data.mlx_ptr, handle_keys, &data);
	mlx_mouse_hook(data.window, mouse_hook, &data);
	mlx_loop(data.mlx_ptr);
}
