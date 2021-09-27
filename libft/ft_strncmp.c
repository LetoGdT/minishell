/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:57:55 by lgaudet-          #+#    #+#             */
/*   Updated: 2020/11/26 22:39:24 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s;
	const unsigned char	*d;

	d = (const unsigned char *)s1;
	s = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*d == *s && *d != '\0' && --n)
	{
		d++;
		s++;
	}
	return (*d - *s);
}
