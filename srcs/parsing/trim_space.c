/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/20 17:16:20 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

static short int	is_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				i++;
			}
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
			{
				i++;
			}
		}
		if (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
			return (SUCCESS);
	}
	return (FAILURE);
}

static short int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	if (!str[i])
		return (SUCCESS);
	return (FAILURE);
}

static int	find_size(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == 0)
		{
			while (str[i] == ' ')
				i++;
		}
		while (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
			i++;
		i++;
		j++;
	}
	return (j);
}

static char	*new_line(char *str, char **line, short int s, short int d)
{
	int		i;
	int		j;
	int		size;

	size = find_size(str);
	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (i == 0)
			while (str[i] == ' ')
				i++;
		if (str[i] == '\'')
			s++;
		if (str[i] == '\"')
			d++;
		while (!(s % 2) && !(d % 2) && is_space_and_next(str, i, ' '))
			i++;
		(*line)[j] = str[i];
		i++;
		j++;
	}
	(*line)[j] = 0;
	return (str);
}

short int	trim_space(char **line)
{
	char		*str;
	int			size;
	short int	s_quote;
	short int	d_quote;

	s_quote = 0;
	d_quote = 0;
	if (is_space(*line))
	{
		if (only_space(*line))
			return (ERROR_SPACE);
		str = ft_strdup(*line);
		if (!str)
			return (FAILURE);
		size = find_size(str);
		*line = ft_realloc(*line, size + 1);
		if (!(*line))
			return (FAILURE);
		if (!new_line(str, line, s_quote, d_quote))
			return (FAILURE);
		free(str);
	}
	return (SUCCESS);
}
