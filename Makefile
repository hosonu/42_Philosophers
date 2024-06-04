# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:53:19 by hosonu            #+#    #+#              #
#    Updated: 2024/06/04 17:57:11 by hoyuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=thread

FILES = src/main.c \
		src/init_data.c \
		src/excute_thread.c \
		src/action.c \
		src/observe.c \
		src/philo_utils.c \
		src/ft_funcs.c

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
