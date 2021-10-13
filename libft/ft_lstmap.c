/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:09:58 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/13 13:21:58 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*curr;

	if (!lst)
		return (NULL);
	ret = ft_lstnew((*f)(lst->content));
	if (!ret)
		return (NULL);
	lst = lst->next;
	curr = ret;
	while (lst)
	{
		curr->next = ft_lstnew((*f)(lst->content));
		if (!curr->next)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		curr = curr->next;
		lst = lst->next;
	}
	return (ret);
}
