/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/21 14:28:06 by mballet          ###   ########.fr       */
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
		if (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
			return (SUCCESS);
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
		while (is_space_and_next(str, i, ' '))
			i++;
		if (i + 1 == (int)ft_strlen(str) - 1 && str[i] == ' ')
			i++;
		i++;
		j++;
	}
	return (j);
}

static char	*new_str(char *new, char **str)
{
	int		i;
	int		j;
	int		size;

	size = find_size(new);
	i = 0;
	j = 0;
	while (new[i] && j < size)
	{
		if (i == 0)
			while (new[i] == ' ')
				i++;
		while (is_space_and_next(new, i, ' '))
			i++;
		if (i + 1 == (int)ft_strlen(new) - 1 && new[i] == ' ')
			i++;
		(*str)[j] = new[i];
		i++;
		j++;
	}
	(*str)[j] = 0;
	return (new);
}

short int	trim_space_export(char **str)
{
	char		*new;
	int			size;

	if (is_space(*str))
	{
		new = ft_strdup(*str);
		if (!new)
			return (FAILURE);
		size = find_size(new);
		*str = ft_realloc(*str, size + 1);
		if (!(*str))
			return (FAILURE);
		if (!new_str(new, str))
			return (FAILURE);
		free(new);
	}
	return (SUCCESS);
}
