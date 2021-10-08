/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 16:30:09 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define ERROR_SPACE 2

static short int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
		i++;
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
		str[j] = str[i];
		i++;
		j++;
	}
	return (j);
}

short int	trim_space(char **line)
{
	int			i;
	int			j;
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
		i = 0;
		j = 0;
		while (str[i] && j < size)
		{
			if (i == 0)
			{
				while (str[i] == ' ')
					i++;
			}
			if (str[i] == '\'')
				s_quote++;
			if (str[i] == '\"')
				d_quote++;
			while (!(s_quote % 2) && !(d_quote % 2) && str[i] == ' ' \
					&& str[i + 1] && str[i + 1] == ' ')
				i++;
			(*line)[j] = str[i];
			i++;
			j++;
		}
		(*line)[j] = 0;
		free(str);
	}
	return (SUCCESS);
}
