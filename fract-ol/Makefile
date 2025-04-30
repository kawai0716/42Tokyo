CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./include/
LIBFT_DIR = ./Libft
LIBFT      = $(LIBFT_DIR)/libft.a
LDFLAGS = -L./minilibx-linux -lmlx_Linux -lX11 -lXext -lm
RM = rm -rf
NAME	= fractol


SRCS =src/burning_ship.c src/share.c src/action.c src/initialization.c src/julia.c src/main.c src/mandelbrot.c src/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "───────────▄───────────"
	@echo "────────▄▀░░░░░░░░▀▄─────"
	@echo "──────▄▀░░░░░░░░░░░░▀▄────"
	@echo "─────█░░░░░░░░░░░░░░░█────"
	@echo "─────█░░░░░░░░░░░░░░░█────"
	@echo "─────█░░░░▄▀▀▀▄░░░▄▀▀▀▄──"
	@echo "─────▄█░░▄▀　　▀▄▀　　▀▄──"
	@echo "────█░░▄▀　　　　　　　▀▄──"
	@echo "────▀▄▀　　　●　　●　　　▀▄─"
	@echo "─────▀▄　　　　▲　　　　　█─"
	@echo "──────▀▄　　　　　　　　▄▀─"
	@echo "────────▀▀▄▄▄▄▄▄▄▄▄▄▄▀▀───"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SILENT: