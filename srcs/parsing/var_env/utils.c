/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_leftover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:29:12 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 13:35:49 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_leftover(char **line, char *str, int loc, int j)
{
	while (str[j])
		(*line)[++loc] = str[++j];
	(*line)[++loc] = 0;
}

short int	fill_value(char *value, char **line, int *loc, char ***esc_quote)
{
	int	i;

	i = -1;
	while (value[i + 1])
	{
		if (value[i + 1] == '\'' || value[i + 1] == '\"')
			if (!fill_esc_quote(esc_quote, *loc + 1))
				return (FAILURE);
		(*line)[++(*loc)] = value[++i];
	}
	return (SUCCESS);
}

short int	malloc_new_line(char **line, char *key, char *value)
{
	*line = ft_realloc(*line, (ft_strlen(*line) - ft_strlen(key) \
		+ ft_strlen(value) + 1));
	if (!(*line))
		return (FAILURE);
	return (SUCCESS);
}
