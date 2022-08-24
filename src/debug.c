/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:37:43 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/30 10:49:22 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_error(int exit_code, char *fatal)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(fatal, STDERR_FILENO);
	exit(exit_code);
}
