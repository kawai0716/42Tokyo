/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:19 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:26:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_rule
{
    /* ── 引数で決まる基本設定 ───────────────────── */
    int             n_philo;      /* 人数＝フォーク数                */
    long            t_die;        /* 食べ始めないと死ぬ猶予 (ms)     */
    long            t_eat;        /* 食べる時間 (ms)                */
    long            t_sleep;      /* 寝る時間 (ms)                  */
    int             must_eat;     /* 目標食事回数 (-1 なら無制限)   */

    /* ── ランタイムで使う共通データ ──────────────── */
    long            start_ms;     /* シミュレーション開始時刻        */
    volatile int    finish;       /* 終了フラグ (0=進行中, 1=終了)  */

    /* ── 同期プリミティブ ──────────────────────── */
    pthread_mutex_t print;        /* 標準出力用ロック                */
    pthread_mutex_t *forks;       /* フォーク (= ミューテックス配列) */
}   t_rule;

typedef struct s_philo
{
    /* ── 自分自身の状態 ─────────────────────────── */
    int             id;           /* 1〜n_philo                      */
    long            last_meal;    /* 最後に食べ始めた時刻 (ms)       */
    int             eat_cnt;      /* 食べた回数                     */

    /* ── フォークへのポインタ ───────────────────── */
    pthread_mutex_t *left;        /* 左フォーク                      */
    pthread_mutex_t *right;       /* 右フォーク                      */

    /* ── スレッド & 全体ルール参照 ──────────────── */
    pthread_t       th;           /* 自分のスレッド ID               */
    t_rule          *rule;        /* 共有ルールへのポインタ          */
}   t_philo;

// typedef struct s_rule
// {
//     int             n_philo;
//     long            t_die;
//     long            t_eat;
//     long            t_sleep;
//     int             must_eat;
//     long            start_ms;
//     volatile int    finish;
//     pthread_mutex_t print;
//     pthread_mutex_t *forks;
// }   t_rule;

// typedef struct s_philo
// {
//     int             id;
//     long            last_eat_time;
//     int             eat_count;
//     pthread_mutex_t *left;
//     pthread_mutex_t *right;
//     pthread_t       th;
//     t_rule          *rule;
// }   t_philo;

#endif
