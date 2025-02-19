CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf obj/

INCS = -I. -I./include -I./Libft -I./printf/include

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

SRC_PATH = src/
OBJ_PATH = obj/
PRINTF_PATH = printf/
PRINTF_SRC_PATH = printf/src/

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_CLIENT_BONUS = client_bonus.c
SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT = $(addprefix $(OBJ_PATH), $(SRC_CLIENT:.c=.o))
OBJ_SERVER = $(addprefix $(OBJ_PATH), $(SRC_SERVER:.c=.o))
OBJ_CLIENT_BONUS = $(addprefix $(OBJ_PATH), $(SRC_CLIENT_BONUS:.c=.o))
OBJ_SERVER_BONUS = $(addprefix $(OBJ_PATH), $(SRC_SERVER_BONUS:.c=.o))

LIBFT = ./Libft/libft.a
FT_PRINTF = ./printf/libftprintf.a

PRINTF_SRC = ft_printf.c ft_printf_di.c ft_printf_p.c ft_printf_u.c \
             ft_printf_x.c ft_printf_x2.c ft_printf_x3.c ft_putchar2.c ft_putstr.c

PRINTF_OBJ = $(addprefix $(OBJ_PATH), $(PRINTF_SRC:.c=.o))

all: $(NAME_CLIENT) $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH)%.o: $(PRINTF_SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(LIBFT):
	make -C Libft

$(FT_PRINTF): $(PRINTF_OBJ)
	ar rcs $(FT_PRINTF) $(PRINTF_OBJ)

$(NAME_CLIENT): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)

$(NAME_SERVER): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)

$(NAME_CLIENT_BONUS): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJ_CLIENT_BONUS) $(LIBFT) $(FT_PRINTF)

$(NAME_SERVER_BONUS): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJ_SERVER_BONUS) $(LIBFT) $(FT_PRINTF)
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

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS) $(FT_PRINTF)

re: fclean all

.PHONY: all clean fclean re bonus
