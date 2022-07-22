/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:32:45 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/21 12:58:31 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_parts(char const *s, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[0] != c && i == 0) || (s[i] != c && s[i - 1] == c && s[i]))
			n++;
		i++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**result;
	int		i;
	int		o;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc((get_parts (s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	index = 0;
	while (index < get_parts (s, c))
	{
		while (s[i] == c && s[i])
			i++;
		o = i;
		while (s[i] != c && s[i])
			i++;
		result[index] = ft_substr(s, o, i - o);
		index++;
	}
	result[index] = NULL;
	return (result);
}
