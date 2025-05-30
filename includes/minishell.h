/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:13 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 18:02:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//通常のプロンプト待ち状態
#define MODE_INTERACTIVE 0
//ヒアドキュメント入力中の状態
#define MODE_HEREDOC     1
//コマンド実行中（子プロセス・パイプ処理中）の状態
#define MODE_EXECUTING   2

int g_shell_mode;

#endif