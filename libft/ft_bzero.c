/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:17:49 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/13 13:21:58 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_bzero(void *pointer, size_t count)
{
	size_t	i;

	i = 0;
	if (count <= 0)
	{
		return (pointer);
	}
	while (i < count)
	{
		((char *)pointer)[i] = 0;
		i++;
	}
	return (pointer);
}
