/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:58:56 by ytouate           #+#    #+#             */
/*   Updated: 2022/07/28 14:17:35 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../Libft/libft.h"
# define BUFFER_SIZE 1
# include<stdio.h> 
# include <fcntl.h> 
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char		*ft_strjoin_gnl(char *s1, char const *s2);
int			ft_strchr_gnl(const char *s, int c);
char		*get_next_line(int fd);
#endif