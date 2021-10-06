/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:26:22 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	starting(t_list **tmp, t_states *st)
{
	t_list	*new;

	new = init_cmds(tmp);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	*st = _DEFAULT;
	return (SUCCESS);
}

static int	restarting(t_list **tmp, int *i)
{
	t_list	*new;

	new = init_cmds(tmp);
	if (!new)
		return (FAILURE);

	ft_lstadd_back(tmp, new);
	// *tmp = ft_lstlast(*tmp);
	(*i) += 2;
	return (SUCCESS);
}

static t_states	which_state(char *str, int i, char c)
{
	if ((c == '>' && str[i + 1] && str[i + 1] == '>') \
		|| (c == '<' && str[i + 1] && str[i + 1] == '<'))
		return (_RED_DOUBLE);
	else if (c == '>' || c == '<')
		return (_RED_SINGLE);
	else if (c == '\'' || c == '\"')
		return (_QUOTES);
	return (_DEFAULT);
}

static short int	fill_in_cmds(t_cmd *content, char *line, int *i, \
		t_states *st)
{
	if (*st == _DEFAULT)
	{
		if (!state_default(content, line, i))
			return (FAILURE);
	}
	// else if (*st == _RED_SINGLE)
	// {
	// 	if (!state_s_redir(cmds, line, i))
	// 		return (FAILURE);
	// }
	// else if (*st == _RED_DOUBLE)
	// {
	// 	if (!state_d_redir(cmds, line, i))
	// 		return (FAILURE);
	// }
	// else if (*st == _QUOTES)
	// {
	// 	if (!state_quotes(cmds, line, i))
	// 		return (FAILURE);
	// }
	return (SUCCESS);
}

short int	tokenizing(t_exec_info **global, char *line)
{
	t_list		*tmp;
	t_states	st;
	int			i;

	tmp = NULL;
	st = _START;
	i = 0;
	while (line[i])
	{
		if (st == _START) {
			if (!starting(&tmp, &st))
				return (FAILURE);
		}
		else if (line[i] == '|')
			if (!restarting(&tmp, &i))
				return (FAILURE);
		st = which_state(line, i, line[i]);
		if (!fill_in_cmds(ft_lstlast(tmp)->content, line, &i, &st))
			return (FAILURE);
		i++;
	}
	(*global)->cmds = tmp;
	return (SUCCESS);
}

//	>>>> j'ai perdu l'adresse du maillon next