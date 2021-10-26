/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 16:51:35 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_states	which_state(char *str, int i, char c, char **esc_quote)
{
	int		j;
	char	*loc;

	loc = NULL;
	if (c == '\'' || c == '\"')
	{
		loc = ft_itoa(i);
		if (esc_quote)
		{
			j = -1;
			while (esc_quote[++j])
				if (!ft_strncmp(loc, esc_quote[j], ft_strlen(loc)))
					return (_DEFAULT);
		}
		return (_QUOTES);
	}
	else if ((c == '>' && str[i + 1] && str[i + 1] == '>') \
		|| (c == '<' && str[i + 1] && str[i + 1] == '<'))
		return (_RED_DOUBLE);
	else if (c == '>' || c == '<')
		return (_RED_SINGLE);
	if (loc)
		free(loc);
	return (_DEFAULT);
}

static short int	fill_in_cmds(t_cmd *content, char *line, int *i, \
		t_norm *norm)
{
	int			ret;
	t_norm_b	norm_b;

	ret = SUCCESS;
	if (norm->st == _DEFAULT)
	{
		norm_b.export = 0;
		norm_b.esc_quote = ft_strdup_double(norm->esc_quote);
		if (!norm_b.esc_quote)
			return (FAILURE);
		if (!state_default(content, line, i, norm_b))
			return (FAILURE);
	}
	else if (norm->st == _RED_SINGLE || norm->st == _RED_DOUBLE)
	{
		ret = state_redir(content, line, i, &(norm->st));
		if (!ret)
			return (FAILURE);
	}
	else if (norm->st == _QUOTES)
	{
		if (!state_quotes(content, line, i, line[*i]))
			return (FAILURE);
	}
	return (ret);
}

short int	tokenizing(t_exec_info *global, char *line, char **esc_quote)
{
	t_list		*tmp;
	t_norm		norm;
	int			i;
	int			ret;
	int			size;

	if (!init_tokenizing(&norm, esc_quote, &tmp, &ret))
		return (norm_free(esc_quote, norm, FAILURE));
	size = ft_strlen(line);
	i = -1;
	while (++i < size)
	{
		if (!token_start(&norm, &tmp, line, &i))
			return (norm_free(esc_quote, norm, FAILURE));
		norm.st = which_state(line, i, line[i], esc_quote);
		ret = fill_in_cmds(ft_lstlast(tmp)->content, line, &i, &norm);
		if (!ret)
			return (norm_free(esc_quote, norm, FAILURE));
	}
	global->cmds = tmp;
	return (norm_free(esc_quote, norm, ret));
}
