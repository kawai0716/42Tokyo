/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:43:03 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/03 19:56:25 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_return(t_list **lst, void (*del)(void *))
{
	if (*lst)
		ft_lstclear(lst, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*result;

	new_list = NULL;
	while (lst)
	{
		result = f(lst->content);
		if (!result)
		{
			free_and_return(&new_list, del);
			return (NULL);
		}
		new_node = ft_lstnew(result);
		if (!new_node)
		{
			del(result);
			free_and_return(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
