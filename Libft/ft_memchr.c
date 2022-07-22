/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:53:18 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 09:50:06 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	size_t			index;
	unsigned char	*string;

	string = ((unsigned char *)s);
	index = 0;
	while (index < n)
	{
		if (string[index] == (unsigned char)c)
		{
			return (string + index);
		}
		index++;
	}
	return (NULL);
}
