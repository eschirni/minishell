# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 14:59:59 by eschirni          #+#    #+#              #
#    Updated: 2022/01/14 18:17:48 by eschirni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = src/main.c	\
		src/error_managment/get_next_line.c	\
		src/error_managment/get_next_line_utils.c

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FILES) -Wall -Werror -Wextra -lreadline -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
