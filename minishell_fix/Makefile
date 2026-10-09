NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft -I./includes
RM = rm -f

LIBFT_DIR =libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRC_DIR = src
BUILTIN_DIR = $(SRC_DIR)/builtin
EXECUTOR_DIR = $(SRC_DIR)/executor
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
SIGNAL_DIR = $(SRC_DIR)/signal
ENV_DIR = $(SRC_DIR)/env
ERROR_DIR = $(SRC_DIR)/error
UTILS_DIR = $(SRC_DIR)/utils
SHELL_DIR = $(SRC_DIR)/shell
PROCESS_DIR = $(SRC_DIR)/process

BUILTIN_SRCS = $(BUILTIN_DIR)/builtin_cd.c \
               $(BUILTIN_DIR)/builtin_cd_utils.c \
               $(BUILTIN_DIR)/builtin_echo.c \
               $(BUILTIN_DIR)/builtin_env.c \
               $(BUILTIN_DIR)/builtin_exit.c \
               $(BUILTIN_DIR)/builtin_exit_utils.c \
               $(BUILTIN_DIR)/builtin_export.c \
               $(BUILTIN_DIR)/builtin_export_utils.c \
               $(BUILTIN_DIR)/builtin_pwd.c \
               $(BUILTIN_DIR)/builtin_unset.c \
               $(BUILTIN_DIR)/builtin_utils.c

EXECUTOR_SRCS = $(EXECUTOR_DIR)/assignment.c \
                $(EXECUTOR_DIR)/assignment_utils.c \
                $(EXECUTOR_DIR)/cmd_exec.c \
                $(EXECUTOR_DIR)/cmd_path.c \
                $(EXECUTOR_DIR)/exec_error.c \
                $(EXECUTOR_DIR)/execute.c \
                $(EXECUTOR_DIR)/heredoc.c \
                $(EXECUTOR_DIR)/heredoc_utils.c \
                $(EXECUTOR_DIR)/pipe_builtin.c \
                $(EXECUTOR_DIR)/pipe.c \
                $(EXECUTOR_DIR)/pipe_error.c \
                $(EXECUTOR_DIR)/pipe_exec.c \
                $(EXECUTOR_DIR)/pipe_redir.c \
                $(EXECUTOR_DIR)/redirect.c \
                $(EXECUTOR_DIR)/utils.c

LEXER_SRCS = $(LEXER_DIR)/lexer.c \
             $(LEXER_DIR)/lexer_expand.c \
             $(LEXER_DIR)/lexer_parse.c \
             $(LEXER_DIR)/lexer_quotes.c \
             $(LEXER_DIR)/lexer_utils.c \
             $(LEXER_DIR)/lexer_var.c \
             $(LEXER_DIR)/lexer_var_split.c \
             $(LEXER_DIR)/lexer_word.c

PARSER_SRCS = $(PARSER_DIR)/parse_cmd_utils.c \
              $(PARSER_DIR)/parse_command.c \
              $(PARSER_DIR)/parse_pipeline.c \
              $(PARSER_DIR)/parser.c \
              $(PARSER_DIR)/parse_redir.c \
              $(PARSER_DIR)/parse_semicolon.c

SIGNAL_SRCS = $(SIGNAL_DIR)/signal.c \
              $(SIGNAL_DIR)/signal_handler.c

ENV_SRCS = $(ENV_DIR)/env_convert.c \
           $(ENV_DIR)/env_dup.c \
           $(ENV_DIR)/env_export.c \
           $(ENV_DIR)/env_init.c \
           $(ENV_DIR)/env_list.c \
           $(ENV_DIR)/env_utils.c

ERROR_SRCS = $(ERROR_DIR)/error.c \
             $(ERROR_DIR)/error_handler.c \
             $(ERROR_DIR)/error_utils.c

UTILS_SRCS = $(UTILS_DIR)/cleanup.c \
             $(UTILS_DIR)/get_next_line.c \
             $(UTILS_DIR)/get_next_line_utils.c \
             $(UTILS_DIR)/wildcard.c \
             $(UTILS_DIR)/wildcard_match.c

SHELL_SRCS = $(SHELL_DIR)/shell_loop.c

PROCESS_SRCS = $(PROCESS_DIR)/process_line.c

SRCS = $(BUILTIN_SRCS) \
       $(EXECUTOR_SRCS) \
       $(LEXER_SRCS) \
       $(PARSER_SRCS) \
       $(SIGNAL_SRCS) \
       $(ENV_SRCS) \
       $(ERROR_SRCS) \
       $(UTILS_SRCS) \
       $(SHELL_SRCS) \
       $(PROCESS_SRCS) \
       $(SRC_DIR)/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) $(LIBFT_LIB)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re