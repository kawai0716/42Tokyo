CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I../../includes -I../../libft

LIBFT_DIR = ../../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS		= ../../src/parser.c \
			  ../../src/parse_command.c \
			  ../../src/parse_redir.c \
			  ../../src/parse_pipeline.c

NAME1		= parser_test
SRCS1		= parser_test.c $(SRCS)
OBJS1		= $(SRCS1:.c=.o)

all: $(NAME1)

$(NAME1): $(OBJS1) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS1)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME1)

re: fclean all

.PHONY: all clean fclean re
