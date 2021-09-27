/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:34:18 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/04 16:04:44 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)(haystack));
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && needle[j] && haystack[i + j]
			&& i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		else
			j = 0;
		i++;
	}
	return (NULL);
}
