/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 13:45:22 by mballet          ###   ########.fr       */
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

static short int	fill_in_cmds(t_exec_info *global, char *line, int *i, \
		t_states *st)
{
	// t_list	*lst;
	// t_list	*tmp;

	// tmp = global->cmds;
	// lst = ft_lstlast(global->cmds);
	// global->cmds = lst;
	if (*st == _START)
	{
		// if (*i == 0)
		// 	tmp = 
		// if (*i != 0)
		// 	global->cmds = global->cmds->next;
		global->cmds = init_cmds();
		if (!(global->cmds))
			return (FAILURE);
		if (!state_default(global->cmds->content, line, i))
			return (FAILURE);
		*st = _DEFAULT;
	}
	else if (*st == _DEFAULT)
	{
		if (!state_default(global->cmds->content, line, i))
			return (FAILURE);
	}
	// else if (*st == _REDIR_SINGLE)
		// if (!state_s_redir(global->cmds->content, line, i))
		// 	return (FAILURE);
	// else if (*st == _REDIR_DOUBLE)
		// if (!state_d_redir(global->cmds->content, line, i))
		// 	return (FAILURE);
	// else if (*st == _QUOTES)
		// if (!state_quotes(global->cmds->content, line, i))
		// 	return (FAILURE);
	// global->cmds = tmp;
	return (SUCCESS);
}

short int	tokenizing(t_exec_info *global, char *line)
{
	t_states	st;
	int			i;

	st = _START;
	i = 0;
	while (line[i])
	{
		if (i != 0 && st == _START)
			st = which_state(line, i, line[i]);
		if (line[i] == '|' && i != 0)
		{
			// st = _START;
			i += 2;
		}
		if (!fill_in_cmds(global, line, &i, &st))
			return (FAILURE);
		i++;
	}
	print_cmds_cmd(global->cmds, global->cmds->content);
	return (SUCCESS);
}

//	faut que je chope le premier maillon de global->cmds
//	pour envoyer la bonne adresse quand je print