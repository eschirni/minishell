# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tom <tom@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 14:59:59 by eschirni          #+#    #+#              #
#    Updated: 2022/01/15 13:20:58 by tom              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = src/main.c	\
		src/gnl/get_next_line.c src/gnl/get_next_line_utils.c	\
		src/executer/exit.c

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FILES) $(CFLAGS) -lreadline -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
