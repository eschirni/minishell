# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tom <tom@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 14:59:59 by eschirni          #+#    #+#              #
#    Updated: 2022/01/14 20:34:08 by tom              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = src/main.c	\
		src/gnl/get_next_line.c src/gnl/get_next_line_utils.c

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FILES) -Wall -Werror -Wextra -lreadline -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
