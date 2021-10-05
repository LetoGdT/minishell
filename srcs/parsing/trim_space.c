/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 14:11:19 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (SUCCESS);
		i++;
	}
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
	int		i;
	int		j;
	char	*str;
	int		size;

	if (is_space(*line))
	{
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
			while (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
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

//	>no need when "" or ''