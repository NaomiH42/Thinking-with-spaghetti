# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:54:08 by ehasalu           #+#    #+#              #
#    Updated: 2023/02/28 20:34:39 by ehasalu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	push_swap
SRCS =	main.c push.c reverse_rotate.c rotate.c swap.c under_five.c utility_stuff.c \
		cases.c arg_check.c utility_stuff2.c utility_stuff3.c utility_stuff4.c \
		utility_stuff5.c arrays.c utility_stuff6.c

LIBFT_F = libft/
LIBFT = libft.a

MAKEFLAGS += --no-print-directory

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_F)
	@cp libft/libft.a .

$(NAME):
	@ echo "            __"
	@ echo "(\,--------'()'--o  WOOF"
	@ echo "(_    ___    /~"
	@ echo "(_)_)  (_)_)"

	@$(CC) $(CFLAGS) $(SRCS) libft.a -o $(NAME)

clean:
	@rm $(NAME)
	@make fclean -C $(LIBFT_F)

fclean: clean
	@rm $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
