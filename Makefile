NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./includes
RM = rm -f

LIBFT_DIR =libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC_DIR = src
BUILTIN_DIR = src/builtin
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(BUILTIN_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME) $(LIBFT_LIB)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	$(RM) $(BUILTIN_DIR)/*.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re