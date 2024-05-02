/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:43:03 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/30 17:16:15 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list = NULL;
    t_list *new_node = NULL;

    while (lst)
    {
        void *result = f(lst->content);
        if (!result)
        {
            if (new_list)
                ft_lstclear(&new_list, del);
            return NULL;
        }
        t_list *new_node = ft_lstnew(result);
        if (!new_node)
        {
            del(result);
            if (new_list)
                ft_lstclear(&new_list, del);
            return NULL;
        }

        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }

    return new_list;
}

