/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:20:04 by ytouate           #+#    #+#             */
/*   Updated: 2021/11/23 18:03:45 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
	{
		return ;
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
int main(int argc, char const *argv[])
{
        int fd;
        char buff[1000];

        if ((fd = open("file.txt",  O_RDWR | O_CREAT )) == -1)
        {
                printf("file opening failed\n");
                exit(0);
        }else{
                ft_putstr_fd("hello", fd);
        }
}
*/