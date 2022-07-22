/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:08:41 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/16 21:27:54 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*casted_src;
	unsigned char	*casted_dst;

	casted_src = (unsigned char *)src;
	casted_dst = (unsigned char *)dst;
	if (casted_dst > casted_src)
	{
		while (len > 0)
		{
			casted_dst[len - 1] = casted_src[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy (casted_dst, casted_src, len);
	}
	return (dst);
}
