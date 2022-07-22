/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:34:45 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/11 16:02:13 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	index;

	index = 0;
	if (dstsize > 0)
	{
		while (src[index] && index < dstsize - 1)
		{
			if (index == dstsize)
			{
				index--;
			}
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	while (src[index] != '\0')
	{
		index++;
	}
	return (index);
}
