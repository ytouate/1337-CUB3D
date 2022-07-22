/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:16:47 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/16 21:07:36 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)

{
	size_t	index;

	index = 0;
	while (((unsigned char)s1[index] || (unsigned char)s2[index]) && index < n)
	{
		if (((unsigned char)s1[index] != (unsigned char)s2[index]))
		{
			return (((unsigned char)s1[index]) - (unsigned char)s2[index]);
		}
		index++;
	}
	return (0);
}
