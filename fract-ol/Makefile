CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I./include/
LDFLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
RM = rm -rf
NAME	= fractol


SRCS = src/action.c src/initialization.c src/julia.c src/main.c src/mandelbrot.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
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

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re