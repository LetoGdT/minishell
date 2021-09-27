/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:20:01 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 18:46:07 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dest, const void *src, int ch, size_t max_size)
{
	const char	*s;
	char		*d;

	s = src;
	d = dest;
	while (max_size-- > 0)
	{
		*d++ = *s++;
		if (*(d - 1) == (unsigned char)ch)
			return (d);
	}
	return (NULL);
}
