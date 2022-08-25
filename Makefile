# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 11:23:28 by ytouate           #+#    #+#              #
#    Updated: 2022/08/12 11:54:52 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FILES = \
	./src/parse_utils3.c 						\
	./src/parse_utils2.c 						\
	./src/parse_utils.c							\
	./src/cub.c									\
	./src/debug.c								\
	./src/map_parse.c							\
	./src/drawing_utils.c						\
	./src/ddaline.c								\
	./src/map_validator.c						\
	./src/map_validator_utils.c					\
	./src/hooks.c								\
	./src/init_functions.c						\
	./get_next_line/get_next_line_utils.c		\
	./get_next_line/get_next_line.c				\

O_FILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(O_FILES)
	cd Libft && make && make bonus && cd ..
	$(CC) $(CFLAGS) ./Libft/libft.a -lmlx -framework OpenGL  -framework AppKit $(O_FILES) -o $(NAME)

clean:
	cd src && rm -f *.o
	cd Libft && make clean && cd ..
	cd get_next_line/ && rm -rf *.o

fclean: clean
	rm -f cub3D
	

re: fclean all

