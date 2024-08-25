#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_stack_elem {
    int value;
    struct s_stack_elem *next;
} t_stack_elem;

typedef struct s_stack {
    t_stack_elem *top;  // スタックのトップ要素へのポインタ
    int size;           // スタック内の要素数
} t_stack;

// スタックの初期化関数
t_stack *init_stack() {
    t_stack *stack = malloc(sizeof(t_stack));  // メモリの確保
    if (stack) {
        stack->top = NULL;  // スタックが空であることを示す
        stack->size = 0;    // スタックのサイズを0に初期化
    }
    return stack;
}

