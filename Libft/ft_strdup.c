/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:04:47 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/11 17:49:26 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*temp_strcpy(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	if (dst == NULL)
	{
		return (NULL);
	}
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
	*dst = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*duplicated_str;

	s1_len = ft_strlen(s1);
	duplicated_str = malloc(s1_len * sizeof(char) + 1);
	if (!duplicated_str)
	{
		return (NULL);
	}
	temp_strcpy (duplicated_str, s1);
	return (duplicated_str);
}
