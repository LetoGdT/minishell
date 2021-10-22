/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/22 17:45:07 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

typedef struct s_quote
{
	int		nbr;
	char	chara;
}	t_quote;

static short int	is_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (SUCCESS);
	}
	return (FAILURE);
}

static int	find_size(char *str)
{
	int		i;
	int		size;
	int		tmp;
	char	quote;

	size = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
		size++;
	}
	i++;
	size++;
	quote = str[i];
	i++;
	size++;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	i++;
	while (str[i] && str[i] != quote)
	{
		i++;
		size++;
	}
	tmp = i;
	i--;
	while (str[i] && str[i] == ' ')
	{
		i--;
		size--;
	}
	i = tmp;
	while (str[i] && !is_separator(str[i]))
	{
		i++;
		size++;
	}
	return (size);
}

static void	new_str(char *new, char **str)
{
	int		i;
	int		j;
	int		tmp;
	char	quote;

	j = 0;
	i = 0;
	while (new[i] && new[i] != '=')
	{
		(*str)[j] = new[i];
		i++;
		j++;
	}
	i++;
	j++;
	quote = new[i];
	i++;
	j++;
	while (new[i] && new[i] == ' ')
	{
		i++;
	}
	while (new[i])
	{
		tmp = i;
		while (new[i] && new[i] == ' ')
		{
			i++;
			if (new[i] == quote)
			{
				tmp = i;
				break ;
			}
		}
		i = tmp;
		if (new[i] == quote)
			break ;
		(*str)[j] = new[i];
		i++;
		j++;
	}
	(*str)[j] = new[i];
	i++;
	j++;
	while (str[i] && !is_separator((*str)[i]))
	{
		(*str)[j] = new[i];
		i++;
		j++;
	}
	(*str)[j] = 0;
}

short int	trim_space_export(char **str)
{
	char	*tmp;
	int		size;

	if (is_space(*str))
	{
		tmp = ft_strdup(*str);
		if (!tmp)
			return (FAILURE);
		size = find_size(tmp);
		printf("size :%d\n", size);
		*str = ft_realloc(*str, size + 1);
		if (!(*str))
			return (FAILURE);
		new_str(tmp, str);
		free(tmp);
	}
	return (SUCCESS);
}
