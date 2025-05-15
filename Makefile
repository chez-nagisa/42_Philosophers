# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhara <nhara@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 12:03:26 by nhara             #+#    #+#              #
#    Updated: 2025/05/15 12:03:29 by nhara            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -pthread #自分のパソコンでやる時は-Werrorを消す
SRCS = src/main.c src/init.c src/routine.c src/thread_monitor.c src/threads_philos.c src/utils.c
OBJS = $(SRCS:.c=.o)
HEADER = ./src/philo.h
INCLUDE = -I $(HEADER)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re