/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/10/21 17:16:36 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

typedef struct s_quote
{
	char		chara;
	short int	nbr;
}	t_quote;

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

static int	space_begenning_end_quote(char *new, int i, t_quote *quote)
{
	int	nbr_diff;

	nbr_diff = i;
	if ((new[i] == '\'' || new[i] == '\"') && !(*quote).nbr)
	{
		(*quote).chara = new[i];
		(*quote).nbr++;
		while (new[i + 1] && new[i + 1] == ' ')
			i++;
	}
	if ((*quote).nbr && new[i + 1] && new[i + 1] == (*quote).chara)
	{
		i++;
		(*quote).nbr++;
	}
	return (i - nbr_diff);
}

static int	find_size(char *str)
{
	int		i;
	int		j;
	t_quote	quote;

	quote.nbr = 0;
	i = 0;
	j = 0;
	while (quote.nbr < 2 && str[i])
	{
		i += space_begenning_end_quote(str, i, &quote);
		while (is_space_and_next(str, i, ' '))
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
	t_quote	quote;

	quote.nbr = 0;
	size = find_size(new);
	i = 0;
	j = 0;
	while (quote.nbr < 2 && new[i] && j < size)
	{
		i += space_begenning_end_quote(new, i, &quote);
		while (is_space_and_next(new, i, ' '))
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
