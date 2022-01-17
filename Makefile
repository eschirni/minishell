# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 14:59:59 by eschirni          #+#    #+#              #
#    Updated: 2022/01/17 19:59:39 by eschirni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILES = src/main.c	\
		src/executer/*.c	\
		utils/*.c

CFLAGS = #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(FILES)
	@gcc $(FILES) $(CFLAGS) -lreadline -o $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
