# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 08:20:25 by lumugot           #+#    #+#              #
#    Updated: 2024/12/02 11:58:48 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = pipex

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = ./libft

LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = pipex.c \
				parsing.c

OBJS        = $(SRCS:.c=.o)


INCLUDES    = -I$(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT) $(NAME)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
