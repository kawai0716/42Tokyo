#======================= 設定値（デフォルトは環境変数で上書き可） =======================
NUM   ?= 4
SLEEP ?= 200
EAT   ?= 200
DIE   ?= 410
TIMES ?= -1

INC      := includes/
UNAME    := $(shell uname -s)    # 例: Linux, Darwin, FreeBSD, MINGW64_NT-10.0-19045
NAME     := philo

SRC      := $(wildcard src/*.c)
OBJ      := $(SRC:%.c=%.o)

CFLAGS   := -Wall -Wextra -Werror -O3 -I$(INC) -g

# ── MSYS2/MinGW では glibc の _FORTIFY_SOURCE が衝突するので無効化
ifneq (,$(findstring MINGW,$(UNAME)))
  CFLAGS += -U_FORTIFY_SOURCE
endif

#======================= コンパイラ判定 =======================
ifeq ($(UNAME),Darwin)
  CC := clang
else ifeq ($(UNAME),FreeBSD)
  CC := clang
else
  CC := gcc        # Linux, MSYS2/MinGW など
endif

LDFLAGS  := -lpthread
RM       := rm -f

#======================= ターゲット =======================
.PHONY: all clean re run show

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean all

run: $(NAME)
	./$(NAME) $(NUM) $(DIE) $(EAT) $(SLEEP) $(TIMES)

show:
	@printf "UNAME   : %s\n" "$(UNAME)"
	@printf "NAME    : %s\n" "$(NAME)"
	@printf "CC      : %s\n" "$(CC)"
	@printf "CFLAGS  : %s\n" "$(CFLAGS)"
	@printf "SRC     : %s\n" "$(SRC)"
	@printf "OBJ     : %s\n" "$(OBJ)"

.PHONY:	all clean re show