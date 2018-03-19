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

NAME = ft_malloc

H_DIR = includes/
C_DIR_MALLOC = srcs/
O_DIR_MALLOC = obj/
PRINTF = ft_printf/

FLAGS = -Wall -Wextra -Werror #-fsanitize=address

C_FILES_MALLOC = ft_malloc.c
O_FILES_MALLOC = $(addprefix $(O_DIR_MALLOC),$(C_FILES_MALLOC:.c=.o))

all: $(NAME)

$(NAME): $(O_FILES_MALLOC)
	make -C $(PRINTF)
	$(CC) $(FLAGS) -o $(NAME) $(O_FILES_MALLOC) -L $(PRINTF) -lftprintf


$(O_FILES_MALLOC): $(O_DIR_MALLOC)%.o: $(C_DIR_MALLOC)%.c
	@mkdir $(O_DIR_MALLOC) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -o $@ -c $< -Iincludes

clean:
	make -C $(PRINTF) clean
	@rm -rf $(O_DIR_MALLOC) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make -C $(PRINTF) fclean
	@rm -rf $(NAME) 2> /dev/null || echo "" > /dev/null

re: fclean all

.PHONY: re clean fclean all