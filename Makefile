# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 18:47:55 by emgarcia          #+#    #+#              #
#    Updated: 2021/10/02 20:13:15 by emgarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_pipex_utils.c ft_process.c main.c
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
