/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_esc_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:06:19 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 14:01:40 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

char	**ft_double_realloc(char **str, size_t size)
{
	char	**str2;
	int		i;

	if (!str)
		return (NULL);
	str2 = malloc(sizeof(char *) * size);
	if (!str2)
	{
		free_double(str);
		return (NULL);
	}
	i = 0;
	while (size > 0 && str[i])
	{
		str2[i] = ft_strdup(str[i]);
		size--;
		i++;
	}
	str2[i] = 0;
	if (str)
		free_double(str);
	return (str2);
}

static void	norm(char ***esc_quote, int last, char *content)
{
	(*esc_quote)[last] = content;
	(*esc_quote)[last + 1] = 0;
}

short int	fill_esc_quote(char ***esc_quote, int loc)
{
	int		last;
	char	*content;

	content = ft_itoa(loc);
	if (!content)
		return (FAILURE);
	if (!*esc_quote)
	{
		*esc_quote = malloc(sizeof(char *) * 1 + 1);
		if (!*esc_quote)
			return (FAILURE);
		norm(esc_quote, 0, content);
	}
	else
	{
		last = 0;
		while ((*esc_quote)[last])
			last++;
		*esc_quote = ft_double_realloc(*esc_quote, last + 1);
		if (!*esc_quote)
			return (FAILURE);
		last--;
		norm(esc_quote, last, content);
	}
	return (SUCCESS);
}
