# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 14:59:59 by eschirni          #+#    #+#              #
#    Updated: 2022/01/14 15:06:18 by eschirni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FILES = src/main.c

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FILES) -Wall -Werror -Wextra -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
