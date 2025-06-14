CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I../../includes -I../../libft

LIBFT_DIR = ../../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

BUILTIN_SRCS = ../../src/builtin/builtin_utils.c \
			   ../../src/builtin/env_utils.c \
			   ../../src/builtin/env_utils2.c \
			   ../../src/builtin/env_utils3.c \
			   ../../src/builtin/builtin_echo.c \
			   ../../src/builtin/builtin_pwd.c \
			   ../../src/builtin/builtin_cd.c \
			   ../../src/builtin/builtin_env.c \
			   ../../src/builtin/builtin_export.c \
			   ../../src/builtin/builtin_unset.c \
			   ../../src/builtin/builtin_exit.c

NAME1		= builtin_test
NAME2		= env_utils_test
NAME3		= builtin_all_test

SRCS1		= builtin_test.c $(BUILTIN_SRCS)
SRCS2		= env_utils_test.c $(BUILTIN_SRCS)
SRCS3		= builtin_all_test.c $(BUILTIN_SRCS)

OBJS1		= $(SRCS1:.c=.o)
OBJS2		= $(SRCS2:.c=.o)
OBJS3		= $(SRCS3:.c=.o)

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJS1) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^

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
	rm -f ../../src/builtin/*.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all clean fclean re
