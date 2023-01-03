# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jileroux <jileroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 10:51:51 by jileroux          #+#    #+#              #
#    Updated: 2022/12/17 14:55:21 by jileroux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################################################################
## ARGUMENTS

NAME = pipex
CFLAGS = -Wall -Werror -Wextra -Iinclude -g3
CC = clang

#####################################################################
## SOURCES

SRC_FILES = src/get_next_line/gnl_utils.c\
			src/get_next_line/gnl.c\
			src/here_doc.c\
			src/parsing.c\
			src/utils_1.c\
			src/utils_2.c\
			src/split.c\
			src/free.c\
			src/main.c\
			src/list.c\
			src/path.c


#####################################################################
## RULES

all: ${NAME}

${NAME}: ${SRC_FILES}
		${CC} ${CFLAGS} ${SRC_FILES} -g -o ${NAME}

%.o: %.c
		${CC} ${CFLAGS} $< -o $@

clean:
		rm -rf *.o

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
