/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:29:50 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:23:13 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *str, int c)
{
	const char	*s;

	s = str - 1;
	while (*++s)
		if (*s == (char)c)
			return ((char *)(s));
	if (*s == (char)c)
		return ((char *)(s));
	return (NULL);
}
