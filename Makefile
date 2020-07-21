# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/17 19:04:30 by sucho             #+#    #+#              #
#    Updated: 2020/07/17 21:31:10 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d
LIBFT			=	libft.a
MINILIBX		=	libmlx.a

CC				=	clang
CFLAGS			=	-Wall -Wextra -Werror -O2

RM				=	rm -f

SRC_PATH		= 	./srcs/
INCLUDES_PATH	=	./includes/
LIBFT_PATH		=	./includes/libft/
MINILIBX_PATH	=	./includes/minilibx_mms_20200219/


LFLAGS			=	-framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore

OBJS			=	${SRC:.c=.o}

.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I{SRC_PATH}

${NAME}:		${OBJS}
				make all -C ${LIBFT_PATH}
				cp ${LIBFT_PATH}${LIBFT} ${MINILIBX}
