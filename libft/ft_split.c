/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:50:00 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/06/22 19:56:03 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	count_strings(char const *str, char *delim)
{
	size_t		i;
	size_t		count;
	size_t		start;

	if (!str || !*str)
		return (1);
	i = -1;
	count = 0;
	start = 0;
	while (++i < ft_strlen(str) + 1)
	{
		if (!is_in_string(str[start], delim))
		{
			if (is_in_string(str[i], delim) || str[i] == '\0')
			{
				count++;
				start = i;
			}
		}
		else
			start = i;
	}
	return (count + 1);
}

static char	*strcpy_split(char const *src, size_t start, size_t end)
{
	char		*ret;
	size_t		i;

	ret = malloc((sizeof(char) * (end - start + 1)));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < end - start)
		ret[i] = src[start + i];
	ret[i] = '\0';
	return (ret);
}

static char	**fail(char **str, int count)
{
	while (count >= 0)
		free(str[count--]);
	free(str);
	return (NULL);
}

static int	init(char const *str, char *delim, char ***ret, size_t *count)
{
	*count = 0;
	if (!str || !*str)
	{
		*ret = malloc(sizeof(char *));
		if (!*ret)
		{
			*ret = NULL;
			return (0);
		}
		**ret = NULL;
		return (0);
	}
	*ret = malloc(sizeof(char *) * count_strings(str, delim));
	if (!*ret)
	{
		*ret = NULL;
		return (0);
	}
	return (1);
}

char	**ft_split(char const *str, char *delim)
{
	char		**ret;
	size_t		i;
	size_t		count;
	size_t		start;

	if (!init(str, delim, &ret, &count))
		return (ret);
	i = -1;
	start = 0;
	while (++i < ft_strlen(str) + 1)
	{
		if (!is_in_string(str[start], delim))
		{
			if (!(is_in_string(str[i], delim) || str[i] == '\0'))
				continue ;
			ret[count] = strcpy_split(str, start, i);
			if (!ret[count++])
				return (fail(ret, (int)count - 1));
			start = i;
		}
		else
			start = i;
	}
	ret[count] = NULL;
	return (ret);
}
