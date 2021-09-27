/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:17:49 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:46:13 by lgaudet-         ###   ########lyon.fr   */
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
