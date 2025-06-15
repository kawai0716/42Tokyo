# コンパイラとフラグ
CC      := cc
CFLAGS  := -Wall -Wextra -Werror

# インクルードディレクトリ（ヘッダ検索パス）
INC_DIR := ../../includes

# libft 関連
LIBFT_DIR := ../../libft
LIBFT     := $(LIBFT_DIR)/libft.a

# ターゲット実行ファイル名
TARGET := test

# ソース／オブジェクトファイル
SRCS := pipe_test.c
OBJS := $(SRCS:.c=.o)

# ──────────────── デフォルトターゲット ────────────────
.PHONY: all
all: $(TARGET)

# ──────────────── ターゲット生成ルール ────────────────
# (1) libft.a がなければ libft ディレクトリでビルドを行う
$(LIBFT):
	@echo ">> libft をビルドしています..."
	@$(MAKE) -C $(LIBFT_DIR)

# (2) 実行ファイルを生成
#     - 先に libft.a をリンクオーダーで指定し、その後にオブジェクトを並べることで
#       未定義シンボルを libft.a から解決できるようにする
$(TARGET): $(LIBFT) $(OBJS)
	@echo ">> 実行ファイル '$(TARGET)' をリンク中..."
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ $(OBJS) $(LIBFT)

# (3) ソースをオブジェクトにコンパイル
#     - ヘッダ検索パスに includes/ を指定
%.o: %.c
	@echo ">> コンパイル中: $<"
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

# ──────────────── クリーンアップ ────────────────
.PHONY: clean
clean:
	@echo ">> オブジェクトファイルを削除中..."
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@echo ">> 実行ファイル '$(TARGET)' と libft.a を削除中..."
	@rm -f $(TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: re
re: fclean all

# ──────────────── その他おまけターゲット ────────────────
.PHONY: libft-re
libft-re:
	@# libft のみを再ビルドしたいときに使う
	@$(MAKE) -C $(LIBFT_DIR) re

