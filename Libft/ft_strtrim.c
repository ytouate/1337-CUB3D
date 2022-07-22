/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:17:53 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/22 21:59:03 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*trimed_str;

	if (!s1)
		return (NULL);
	trimed_str = NULL;
	start = 0;
	i = 0;
	end = ft_strlen (s1);
	while (*s1 && ft_search (s1[start], set) == 1)
		start++;
	while (end > start && ft_search (s1[end - 1], set) == 1)
		end--;
	trimed_str = (char *)malloc ((end - start + 1) * sizeof(char));
	if (!trimed_str)
		return (NULL);
	while (end > start)
	{
		trimed_str[i++] = s1[start++];
	}
	trimed_str[i] = '\0';
	return (trimed_str);
}
