/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:46:32 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 08:43:04 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*string_1;
	unsigned char	*string_2;

	index = 0;
	string_1 = ((unsigned char *)s1);
	string_2 = ((unsigned char *)s2);
	while (index < n)
	{
		if (string_1[index] != string_2[index])
		{
			return (string_1[index] - string_2[index]);
		}
		index++;
	}
	return (0);
}
