# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/02/14 14:25:17 by lbertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC		= cub3d.c \
			keyboard.c \
			move.c \
			sprites.c \
			window.c \
			hooks/action_hooks.c \
			hooks/motion_hooks.c \
			parsing/map_parser.c \
			parsing/map_validation.c \
			parsing/parser.c \
			parsing/settings_parser.c \
			parsing/sprite_parser.c \
			parsing/textures_parser.c \
			parsing/textures_parser2.c \
			render/hud.c \
			render/pixel.c \
			render/render.c \
			render/wallcaster.c \
			render/spritecaster.c \
			utils/bmpimage.c \
			utils/collision.c \
			utils/color.c \
			utils/direction.c \
			utils/error.c \
			utils/rgbint.c \
			utils/time.c \
			utils/validate.c
SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes/cub3d.h
MLX		= ./mlx
NAME	= cub3d
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3

srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS}

${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	@${MAKE} -C ${MLX}
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
