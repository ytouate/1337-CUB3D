/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 17:39:55 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 11:52:20 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*string;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	string = malloc(j + 1 * sizeof(char));
	if (!string)
	{
		return (NULL);
	}
	while (s[i] && i < j)
	{
		string[i] = f(i, s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
