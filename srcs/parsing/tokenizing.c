/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 16:17:51 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_states	which_state(char *str, int i, char c)
{
	if ((c == '>' && str[i + 1] && str[i + 1] == '>') \
		|| (c == '<' && str[i + 1] && str[i + 1] == '<'))
		return (_REDIR_DOUBLE);
	else if (c == '>' || c == '<')
		return (_REDIR_SINGLE);
	else if (c == '\'' || c == '\"')
		return (_QUOTES);
	return (_DEFAULT);
}

static short int	fill_in_cmds(t_cmd *cmds, char *line, int *i, \
		t_states *st)
{
	if (*st == _DEFAULT)
	{
		if (!state_default(cmds, line, i))
			return (FAILURE);
	}
	// else if (*st == _REDIR_SINGLE)
	// {
	// 	if (!state_s_redir(cmds, line, i))
	// 		return (FAILURE);
	// }
	// else if (*st == _REDIR_DOUBLE)
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
		if (st == _START)
		{
			if (!init_cmds(&((*global)->cmds)))
				return (FAILURE);
			tmp = (*global)->cmds;
			st = _DEFAULT;
		}
		if (line[i] == '|' && st != _START)
		{
			if (!init_cmds(&((*global)->cmds)))
				return (FAILURE);
			(*global)->cmds = ft_lstlast((*global)->cmds);
			i += 2;
		}
		st = which_state(line, i, line[i]);
		if (!fill_in_cmds((*global)->cmds->content, line, &i, &st))
			return (FAILURE);
		// (*global)->cmds = ft_lstlast((*global)->cmds);
		i++;
	}
	(*global)->cmds = tmp;
	// while ((*global)->cmds)
	// {
	// 	printf("list cmds :\033[33m\n");
	// 	print_cmds_cmd((*global)->cmds->content);
	// 	(*global)->cmds = (*global)->cmds->next;
	// }
	// (*global)->cmds = tmp;
	return (SUCCESS);
}

//	>>>> j'ai perdu l'adresse du maillon next