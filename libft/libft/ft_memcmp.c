/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:19:17 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:31:53 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	const unsigned char		*d;
	const unsigned char		*s;

	if (size == 0)
		return (0);
	d = (const unsigned char *)ptr1;
	s = (const unsigned char *)ptr2;
	while (--size && *d == *s)
	{
		d++;
		s++;
	}
	return ((int)(*d - *s));
}
