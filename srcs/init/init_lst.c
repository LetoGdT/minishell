/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:37:21 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 11:37:37 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init_lst(t_list **lst, int size)
{
	char	*str;

	str = malloc(sizeof(char) * size);
	if (!str)
		return (FAILURE);
	str[0] = '0';
	str[1] = 0;
	*lst = ft_lstnew(str);
	if (!(*lst))
		return (FAILURE);
	return (SUCCESS);
}