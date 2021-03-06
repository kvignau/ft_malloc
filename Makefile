# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvignau <kvignau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/04 10:52:32 by kvignau           #+#    #+#              #
#    Updated: 2016/03/23 19:49:01 by kvignau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_malloc.so
NNAME = libft_malloc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

H_DIR = includes/
C_DIR_MALLOC = srcs/
O_DIR_MALLOC = obj/
LIB = libft/

CC = gcc
FLAGS = -Wall -Wextra -Werror

C_FILES_MALLOC = ft_malloc.c
C_FILES_MALLOC += ft_free.c
C_FILES_MALLOC += ft_realloc.c
C_FILES_MALLOC += ft_lib_malloc.c
C_FILES_MALLOC += ft_display_malloc.c
O_FILES_MALLOC = $(addprefix $(O_DIR_MALLOC),$(C_FILES_MALLOC:.c=.o))

all: $(NAME)

$(NAME): $(O_FILES_MALLOC)
	make -C $(LIB)
	$(CC) $(FLAGS) -shared -o $(NNAME)_$(HOSTTYPE).so $(O_FILES_MALLOC) -L $(LIB) -lft
	@ln -sf $(NNAME)_$(HOSTTYPE).so "libft_malloc.so"


$(O_FILES_MALLOC): $(O_DIR_MALLOC)%.o: $(C_DIR_MALLOC)%.c
	@mkdir $(O_DIR_MALLOC) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	make -C $(LIB) clean
	@rm -rf $(O_DIR_MALLOC) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make -C $(LIB) fclean
	@rm -f $(NNAME)_$(HOSTTYPE).so "libft_malloc.so" 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: re clean fclean all
