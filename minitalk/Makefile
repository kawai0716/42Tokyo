CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include
RM = rm -f

FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

LIBFT_DIR = ft_printf/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC = src/client.c src/server.c
BONUS_SRC = src/client_bonus.c src/server_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

NAME_CLIENT = client
NAME_SERVER = server
BONUS_CLIENT = client_bonus
BONUS_SERVER = server_bonus

all: $(LIBFT_LIB) $(FT_PRINTF_LIB) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF_LIB):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(NAME_CLIENT): src/client.o $(FT_PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) src/client.o $(FT_PRINTF_LIB) $(LIBFT_LIB)

$(NAME_SERVER): src/server.o $(FT_PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) src/server.o $(FT_PRINTF_LIB) $(LIBFT_LIB)
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

bonus: fclean $(LIBFT_LIB) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(BONUS_CLIENT) src/client_bonus.c $(FT_PRINTF_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $(BONUS_SERVER) src/server_bonus.c $(FT_PRINTF_LIB) $(LIBFT_LIB)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(FT_PRINTF_DIR)
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(FT_PRINTF_DIR)
	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(BONUS_CLIENT) $(BONUS_SERVER)

re: fclean all

.PHONY: all clean fclean re bonus


# CC = gcc
# CFLAGS = -Wall -Werror -Wextra
# RM = rm -rf obj/

# INCS = -I. -I./include -I./Libft -I./printf/include

# NAME_CLIENT = client
# NAME_SERVER = server
# NAME_CLIENT_BONUS = client_bonus
# NAME_SERVER_BONUS = server_bonus

# SRC_PATH = src/
# OBJ_PATH = obj/
# PRINTF_PATH = printf/
# PRINTF_SRC_PATH = printf/src/

# SRC_CLIENT = client.c
# SRC_SERVER = server.c
# SRC_CLIENT_BONUS = client_bonus.c
# SRC_SERVER_BONUS = server_bonus.c

# OBJ_CLIENT = $(addprefix $(OBJ_PATH), $(SRC_CLIENT:.c=.o))
# OBJ_SERVER = $(addprefix $(OBJ_PATH), $(SRC_SERVER:.c=.o))
# OBJ_CLIENT_BONUS = $(addprefix $(OBJ_PATH), $(SRC_CLIENT_BONUS:.c=.o))
# OBJ_SERVER_BONUS = $(addprefix $(OBJ_PATH), $(SRC_SERVER_BONUS:.c=.o))

# LIBFT = ./Libft/libft.a
# FT_PRINTF = ./printf/libftprintf.a

# PRINTF_SRC = ft_printf.c ft_printf_di.c ft_printf_p.c ft_printf_u.c \
#              ft_printf_x.c ft_printf_x2.c ft_printf_x3.c ft_putchar2.c ft_putstr.c

# PRINTF_OBJ = $(addprefix $(OBJ_PATH), $(PRINTF_SRC:.c=.o))

# all: $(NAME_CLIENT) $(NAME_SERVER)

# bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

# $(OBJ_PATH)%.o: $(SRC_PATH)%.c
# 	@mkdir -p $(OBJ_PATH)
# 	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

# $(OBJ_PATH)%.o: $(PRINTF_SRC_PATH)%.c
# 	@mkdir -p $(OBJ_PATH)
# 	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

# $(LIBFT):
# 	make -C Libft

# $(FT_PRINTF): $(PRINTF_OBJ)
# 	ar rcs $(FT_PRINTF) $(PRINTF_OBJ)

# $(NAME_CLIENT): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT)
# 	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)

# $(NAME_SERVER): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER)
# 	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)

# $(NAME_CLIENT_BONUS): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT_BONUS)
# 	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJ_CLIENT_BONUS) $(LIBFT) $(FT_PRINTF)

# $(NAME_SERVER_BONUS): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER_BONUS)
# 	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJ_SERVER_BONUS) $(LIBFT) $(FT_PRINTF)
# 	@echo "───────────▄───────────"
# 	@echo "────────▄▀░░░░░░░░▀▄─────"
# 	@echo "──────▄▀░░░░░░░░░░░░▀▄────"
# 	@echo "─────█░░░░░░░░░░░░░░░█────"
# 	@echo "─────█░░░░░░░░░░░░░░░█────"
# 	@echo "─────█░░░░▄▀▀▀▄░░░▄▀▀▀▄──"
# 	@echo "─────▄█░░▄▀　　▀▄▀　　▀▄──"
# 	@echo "────█░░▄▀　　　　　　　▀▄──"
# 	@echo "────▀▄▀　　　●　　●　　　▀▄─"
# 	@echo "─────▀▄　　　　▲　　　　　█─"
# 	@echo "──────▀▄　　　　　　　　▄▀─"
# 	@echo "────────▀▀▄▄▄▄▄▄▄▄▄▄▄▀▀───"

# clean:
# 	$(RM) $(OBJ_PATH)

# fclean: clean
# 	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS) $(FT_PRINTF)

# re: fclean all

# .PHONY: all clean fclean re bonus
