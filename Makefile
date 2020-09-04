# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/02 18:03:49 by sucho             #+#    #+#              #
#    Updated: 2020/09/02 20:38:36 by sucho            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3d
LIBFT			=	libft.a
MINILIBX		=	libmlx.a

CC				=	clang
CFLAGS			=	-Wall -Wextra -Werror -O2

RM				=	rm -f

SRC_PATH		=	./srcs/
INCLUDES_PATH	=	./includes/
LIBFT_PATH		=	./includes/libft/
MINILIBX_PATH	=	./includes/minilibx_mms_20200219/

SRCS			=	untextured_raycast.c\
					untextured_key_press.c\
					map_info.c

LFLAGS			=	-framework Cocoa -framework Metal -framework MetalKit -framework QuartzCore

OBJS			=	${SRC_PATH:.c=.o}

.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I{SRC_PATH}

all: 			$(NAME)

${NAME}:		${OBJS}
				make all -C ${LIBFT_PATH}
				cp ${LIBFT_PATH}${LIBFT} ${MINILIBX}
				$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LFLAGS)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				rm -f $(OBJS)

fclean: 		clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				rm -f $(NAME)

re: 			fclean all

.PHONY: 		test bonus all clean fclean re
