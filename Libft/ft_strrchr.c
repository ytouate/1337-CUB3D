/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:00:05 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/11 16:02:51 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	lenght;

	lenght = ft_strlen ((char *)s);
	while ((lenght > 0) && (*s != '\0') && (s[lenght] != (char)c))
	{
		lenght--;
	}
	if (s[lenght] == (char)c)
	{
		return ((char *)s + lenght);
	}
	return (NULL);
}
