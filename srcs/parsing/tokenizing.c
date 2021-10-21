/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/21 10:22:32 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	starting(t_list **tmp, t_states *st)
{
	t_list	*new;

	new = init_content();
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	*st = _DEFAULT;
	return (SUCCESS);
}

static int	restarting(char *line, t_list **tmp, int *i)
{
	t_list	*new;

	new = init_content();
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	(*i)++;
	if (line[(*i)] == ' ')
		(*i)++;
	return (SUCCESS);
}

static t_states	which_state(char *str, int i, char c)
{
	if (c == '\'' || c == '\"')
		return (_QUOTES);
	else if ((c == '>' && str[i + 1] && str[i + 1] == '>') \
		|| (c == '<' && str[i + 1] && str[i + 1] == '<'))
		return (_RED_DOUBLE);
	else if (c == '>' || c == '<')
		return (_RED_SINGLE);
	return (_DEFAULT);
}

static short int	fill_in_cmds(t_cmd *content, char *line, int *i, \
		t_states *st)
{
	int	ret;

	ret = SUCCESS;
	if (*st == _DEFAULT)
	{
		if (!state_default(content, line, i))
			return (FAILURE);
	}
	else if (*st == _RED_SINGLE || *st == _RED_DOUBLE)
	{
		ret = state_redir(content, line, i, st);
		if (!ret)
			return (FAILURE);
	}
	else if (*st == _QUOTES)
	{
		if (!state_quotes(content, line, i, line[*i]))
			return (FAILURE);
	}
	return (ret);
}

short int	tokenizing(t_exec_info *global, char *line)
{
	t_list		*tmp;
	t_states	st;
	int			i;
	int			ret;
	int			size;

	tmp = NULL;
	st = _START;
	ret = SUCCESS;
	size = ft_strlen(line);
	i = 0;
	while (i < size)
	{
		if (st == _START)
		{
			if (!starting(&tmp, &st))
				return (FAILURE);
		}
		else if (line[i] == '|')
			if (!restarting(line, &tmp, &i))
				return (FAILURE);
		st = which_state(line, i, line[i]);
		ret = fill_in_cmds(ft_lstlast(tmp)->content, line, &i, &st);
		if (!ret)
			return (FAILURE);
		i++;
	}
	global->cmds = tmp;
	return (ret);
}
