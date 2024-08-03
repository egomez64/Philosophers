NAME = philo

CC = cc

SRCS = src/main.c \
	src/parsing.c \
	src/init.c \
	src/handle_threads.c \
	src/forks.c \
	src/routine.c \
	src/destroy.c \
	utils/ft_atoi.c \
	utils/ft_calloc.c \
	utils/ft_bzero.c \
	utils/time.c \

HEADERS = includes/philo.h

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Iincludes
LDFLAGS = -lpthread

ifdef DEBUG
CFLAGS = -Wall -Wextra -g
endif

ifdef CHECK
CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
