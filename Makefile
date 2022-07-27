# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 11:23:28 by ytouate           #+#    #+#              #
#    Updated: 2022/07/27 11:31:48 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
# CFLAGS = -Wall -Wextra -Werror 
FILES = \
	./cub.c		\
	./debug.c	\

O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(O_FILES)
	cd Libft && make && make bonus && cd ..
	$(CC) $(CFLAGS) ./Libft/libft.a -lmlx -framework OpenGL -framework AppKit $(O_FILES) -o $(NAME)

clean:
	rm -f cub3D
	cd Libft && make clean && cd ..

libft:
	cd Libft && make && cd ..