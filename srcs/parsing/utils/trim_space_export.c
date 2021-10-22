/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/22 18:13:49 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

typedef struct s_quote
{
	int		nbr;
	char	chara;
}	t_quote;

static void	norm_before_equal(char *str, int *i, int *size)
{
	while (str[*i] && str[*i] != '=')
	{
		(*i)++;
		(*size)++;
	}
	(*i)++;
	(*size)++;
}

static int	find_size(char *str)
{
	int		i;
	int		size;
	int		tmp;
	char	quote;

	size = 0;
	i = 0;
	norm_before_equal(str, &i, &size);
	quote = str[i];
	i++;
	size++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[++i] && str[i] != quote)
		size++;
	tmp = i;
	while (str[--i] && str[i] == ' ')
		size--;
	i = tmp;
	while (str[++i] && !is_separator(str[i]))
		size++;
	return (size);
}

static void	fill_str_btw_quote(char *new, char **str, int *i, int *j)
{
	int		tmp;
	char	quote;

	quote = new[(*i)++];
	(*j)++;
	while (new[*i] && new[*i] == ' ')
		(*i)++;
	while (new[*i])
	{
		tmp = *i;
		while (new[*i] && new[*i] == ' ')
		{
			(*i)++;
			if (new[*i] == quote)
			{
				tmp = *i;
				break ;
			}
		}
		*i = tmp;
		if (new[*i] == quote)
			break ;
		(*str)[(*j)++] = new[(*i)++];
	}
}

static void	new_str(char *new, char **str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (new[i] && new[i] != '=')
		(*str)[j++] = new[i++];
	i++;
	j++;
	fill_str_btw_quote(new, str, &i, &j);
	(*str)[j++] = new[i++];
	while (str[i] && !is_separator((*str)[i]))
		(*str)[j++] = new[i++];
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
		*str = ft_realloc(*str, size + 1);
		if (!(*str))
			return (FAILURE);
		new_str(tmp, str);
		free(tmp);
	}
	return (SUCCESS);
}
