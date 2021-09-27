# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 18:47:55 by emgarcia          #+#    #+#              #
#    Updated: 2021/09/27 16:49:52 by emgarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c
OBJS	=	${SRCS:.c=.o}
LIBFT	=	libft/libft.a
NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

clean:
	@cd libft ; make fclean
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
