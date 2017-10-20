#!/usr/bin/make -f
NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INC = -I inc
SRC_DIR = src
SRC = \
	dispatcher\
	ft_isdigit\
	ft_islower\
	ft_isupper\
	ft_memalloc\
	ft_memcpy\
	ft_memset\
	ft_printf\
	ft_strdup\
	ft_strlen\
	ft_strnlen\
	ft_strupcase\
	ft_tolower\
	ft_toupper\
	int_handlers\
	int_handlers_deprecated\
	parser\
	print_char\
	print_float\
	print_int\
	util
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Building $@..."
	@ar -rcs $@ $(OBJ)
	@echo "Done."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all
