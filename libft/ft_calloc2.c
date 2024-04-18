/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:44:23 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/18 19:44:26 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc関数のために必要

void *calloc_with_malloc(size_t num_elements, size_t size_of_element) {
    size_t total_size = num_elements * size_of_element; // 確保するメモリ領域の合計サイズ

    // malloc関数を使用してメモリ領域を確保する
    void *ptr = malloc(total_size);

    if (ptr != NULL) {
        // 確保したメモリ領域をゼロで初期化する
        // memset関数を使用してゼロで初期化することもできます
        for (size_t i = 0; i < total_size; i++) {
            *((char *)ptr + i) = 0;
        }
    }

    return ptr;
}
