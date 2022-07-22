/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:53:07 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 10:34:07 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)

{
	void	*ptr;

	ptr = malloc (count * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero (ptr, count * size);
	return (ptr);
}
