/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:09:58 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:43:35 by lgaudet-         ###   ########lyon.fr   */
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
