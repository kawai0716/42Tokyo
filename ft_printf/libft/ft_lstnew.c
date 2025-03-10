/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:51:54 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/28 17:47:12 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pd;

	pd = (t_list *)malloc(sizeof(t_list));
	if (!pd)
		return (NULL);
	pd->content = content;
	pd->next = NULL;
	return (pd);
}
