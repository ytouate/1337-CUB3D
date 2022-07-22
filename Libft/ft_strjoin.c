/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:14:49 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 15:10:09 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	char	*saved;

	saved = dst;
	while (*src)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (saved);
}

static char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	char	*string;

	dst_len = ft_strlen (dst);
	string = dst + dst_len;
	while (*src)
	{
		*string++ = *src++;
	}
	*string = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;

	if (!s1)
		return (NULL);
	string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_strcpy (string, s1);
	ft_strcat (string, s2);
	return (string);
}
