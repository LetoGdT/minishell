/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:29:50 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/13 13:21:58 by mballet          ###   ########.fr       */
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
