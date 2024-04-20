/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:40:09 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/20 20:37:07 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (d < s)
	{
		// コピー元の方がコピー先よりも高いアドレスにある場合
		// 前から順番にコピーする
		while (len-- != 0)
			*d++ = *s++;
	}
	else if (d > s)
	{
		// コピー先の方がコピー元よりも高いアドレスにある場合
		// 後ろから逆順にコピーする
		while (len-- != 0)
			*--d = *--s;
	}
	else
	{
		// コピー元とコピー先が同じ領域の場合は何もしない
		// (この処理は必須ではありませんが、安全側に倒しています)
	}
	return (dest);
}

// void *ft_memmove(void *dest, const void *src, size_t len)
// {
// 	size_t i;
// 	i=0;
// 	char *b;
// 	char *d=dest;
// 	const char *s=src;
// 	if(d == '\0' || s == '\0')
// 		return(NULL);
// 	while(i<n)
// 	{
// 		d=s;
// 	}
// }