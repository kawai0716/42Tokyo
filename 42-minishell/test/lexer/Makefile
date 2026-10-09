CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I../../includes -I../../libft

LIBFT_DIR = ../../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS		= ../../src/lexer.c \
			  ../../src/lexer2.c \
			  ../../src/lexer3.c

NAME1		= lexer_test
NAME2		= lexer_test_cases
NAME3		= lexer_test_unit
SRCS1		= lexer_test.c $(SRCS)
SRCS2		= lexer_test_cases.c $(SRCS)
SRCS3		= lexer_test_unit.c $(SRCS)
OBJS1		= $(SRCS1:.c=.o)
OBJS2		= $(SRCS2:.c=.o)
OBJS3		= $(SRCS3:.c=.o)

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJS1) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

$(NAME2): $(OBJS2) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME3): $(OBJS3) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS1) $(OBJS2) $(OBJS3)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all clean fclean re
