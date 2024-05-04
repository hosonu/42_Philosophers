# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:53:19 by hosonu            #+#    #+#              #
#    Updated: 2024/05/01 17:53:22 by hosonu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

FILES = philosophers.c

SRCS = $(FILES)
OBJS = $(SRCS:.c=.o)
HEAD = philosophers.h
LIBFT = ./libft

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I $(HEAD) -L$(LIBFT) -lft -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re all
