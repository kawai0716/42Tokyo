# Makefile for Philosophers project

NAME = philosophers
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes/
RM = rm -f

SRC = main.c
SRCS = $(addprefix src/, $(SRC))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT: