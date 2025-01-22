# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:53:19 by hosonu            #+#    #+#              #
#    Updated: 2024/08/26 20:42:00 by hosonu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES = main.c \
		init_data.c \
		excute_thread.c \
		action.c \
		observe.c \
		philo_utils.c \
		ft_funcs.c

SRCS = $(FILES)
OBJS = $(SRCS:.c=.o)
HEAD = ./philosophers.h

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(HEAD) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re all
