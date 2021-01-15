# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/01/15 14:59:30 by lbertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC		= cub3d.c \
			window.c \
			utils/parsing/map_parser.c \
			utils/parsing/parser.c \
			utils/parsing/settings_parser.c \
			utils/parsing/textures_parser.c \
			utils/error.c \
			utils/is_valid.c \
			utils/rgbint.c
SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes/cub3d.h
MLX		= ./mlx
NAME	= cub3d
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS}

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	@${MAKE} -C ${MLX}
	cp libft/libft.a ${NAME}
	${CC} -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME} ${OBJS} libft/libft.a ${MLX}/libmlx.a

all: ${NAME}

clean:
	${MAKE} clean -C ./libft
	${MAKE} clean -C ${MLX}
	${RM} ${OBJS}
	${RM} a.out

fclean: clean
	${MAKE} fclean -C ./libft
	${MAKE} clean -C ${MLX}
	${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re .c.o
