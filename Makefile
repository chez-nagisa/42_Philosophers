NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -pthread
SRCS = src/main.c src/init.c src/routine.c src/thread_monitor.c src/threads_philos.c src/utils.c
OBJS = $(SRCS:.c=.o)
HEADER = ./src/philo.h
INCLUDE = -I $(HEADER)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re