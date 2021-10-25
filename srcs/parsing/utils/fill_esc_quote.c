/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_esc_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:06:19 by mballet           #+#    #+#             */
/*   Updated: 2021/10/25 16:20:40 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_double_realloc(char **str, size_t size)
{
	char	**str2;
	int		i;

	// printf("HERE 1\n");
	if (!str)
		return (NULL);
	str2 = malloc(sizeof(char*) * size);
	if (!str2)
	{
		if (str)
		{
			i = 0;
			while (str[i])
			{
				if (str[i])
					free(str[i]);
				i++;
			}
			free(str);
		}
		return (NULL);
	}
	// printf("HERE 2\n");
	i = 0;
	while (size > 0 && str[i])
	{
		str2[i] = ft_strdup(str[i]);
		size--;
		i++;
	}
	// printf("HERE 3\n");
	str2[i] = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i])
				free(str[i]);
			i++;
		}
		free(str);
	}
	// printf("HERE 4\n");
	return (str2);
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
		*esc_quote = malloc(sizeof(char*) * 1 + 1);
		if (!*esc_quote)
			return (FAILURE);
		(*esc_quote)[0] = content;
		(*esc_quote)[1] = 0;
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
		(*esc_quote)[last] = content;
		(*esc_quote)[last + 1] = 0;
	}
	return (SUCCESS);
}