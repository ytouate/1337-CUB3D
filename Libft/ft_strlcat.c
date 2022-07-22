/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:38:48 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 15:29:41 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)

{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen (src);
	if (dstsize == 0)
		return (s_len);
	d_len = ft_strlen(dst);
	if (dstsize < d_len + 1)
		return (s_len + dstsize);
	if (dstsize > d_len + 1)
	{
		i = 0;
		while (src[i] && i < (dstsize - d_len -1))
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
	}
	return (d_len + s_len);
}
