# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tom <tom@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 11:22:27 by tom               #+#    #+#              #
#    Updated: 2022/01/18 16:56:59 by tom              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FLAGS
CC = gcc
CFLAGS = #-Wall -Wextra -Werror

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# EXECUTABLE
NAME = ./minishell

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./obj/
# UTILS_PATH = $(SRC_PATH)utils/

# SOURCES
SRC =	$(SRC_PATH)main.c \
		src/executer/*.c src/utils/*.c 

# OBJECTS
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# RULES
all: $(NAME)
	@echo $(G)"         .__         .__         .__             .__   .__   "$(X)
	@echo $(G)"  _____  |__|  ____  |__|  ______|  |__    ____  |  |  |  |  "$(X)
	@echo $(G)" /     \ |  | /    \ |  | /  ___/|  |  \ _/ __ \ |  |  |  |  "$(X)
	@echo $(G)"|  Y Y  \|  ||   |  \|  | \___ \ |   Y  \   ___/ |  |__|  |__"$(X)
	@echo $(G)"|__|_|  /|__||___|  /|__|/____  >|___|  / \___  >|____/|____/"$(X)
	@echo $(G)"      \/          \/          \/      \/      \/             "$(X)
	@printf "\n\n"

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -lreadline -c -o $@ $<
	@echo $(G)Finished [$@]$(X)

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(SRC)]
	@echo into [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
			rm -f -r $(OBJ_PATH); \
			echo $(R)Cleaning" "[$(OBJ) $(OBJ_PATH)]...$(X); else \
			echo "No objects to remove."; \
	fi;

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]...$(X);else \
			echo "No executable to remove."; \
	fi;

re: fclean all

# ADDITIONAL RULES

norm:
	@echo $(G)Checking Norminette...$(X)
	@norminette | grep Error | egrep --color '.*Error!|$$' || true
	@echo $(G)Done$(X)

.PHONY: all, clean, fclean, re, norm
