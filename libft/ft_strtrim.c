/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:50:32 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/04 16:02:57 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	in_char_set(char c, const char *char_set)
{
	const char	*set;

	set = char_set - 1;
	while (*++set)
		if (c == *set)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *str, char const *char_set)
{
	int		start;
	int		end;
	int		i;
	char	*ret;

	if (!str || !char_set)
		return (NULL);
	start = 0;
	while (str[start] && in_char_set(str[start], char_set))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && in_char_set(str[end], char_set))
		end--;
	ret = malloc((sizeof(char) * (end - start + 2)));
	if (!ret)
		return (NULL);
	i = 0;
	while (start <= end)
		ret[i++] = str[start++];
	ret[i] = '\0';
	return (ret);
}
