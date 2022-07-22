/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:44:53 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/23 14:05:33 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	j;

	if (!s)
	{
		return ;
	}
	j = (unsigned int)ft_strlen(s);
	i = 0;
	while (s[i] && i < j)
	{
		f(i, &s[i]);
		i++;
	}
}
