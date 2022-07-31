# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 11:23:28 by ytouate           #+#    #+#              #
#    Updated: 2022/07/30 10:09:57 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc -fsanitize=address -g
# CFLAGS = -Wall -Wextra -Werror 
FILES = \
	./cub.c		\
	./debug.c	\
	./get_next_line/get_next_line_utils.c	\
	./get_next_line/get_next_line.c			\
	./map_parse.c							\
	./map_check.c

O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(O_FILES)
	cd Libft && make && make bonus && cd ..
	$(CC) $(CFLAGS) ./Libft/libft.a -lmlx -framework OpenGL -framework AppKit $(O_FILES) -o $(NAME)

clean:
	rm -f cub3D
	rm -f *.o
	cd Libft && make clean && cd ..

libft:
	cd Libft && make && cd ..