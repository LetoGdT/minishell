/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 12:17:31 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start(t_list **tmp, t_states *st, char c, int *i)
{
	t_list	*new;

	new = init_content();
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	*st = _DEFAULT;
	if (c == '|')
		(*i)++;
	return (SUCCESS);
}

static short int	find_token_str(t_token *token, char *line, int *i, char **esc_quote)
{
	int		j;
	char	quote;

	token->str = malloc(sizeof(char) * find_size_token(line, *i) + 1);
	if (!token->str)
		return (FAILURE);
	j = 0;
	while (line[*i] && line[*i] != ' ')
	{
		if (is_quote_export(line[*i], esc_quote, *i))
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
			{
				token->str[j] = line[*i];
				(*i)++;
				j++;
			}
			(*i)++;
			continue ;
		}
		token->str[j] = line[*i];
		(*i)++;
		j++;
	}
	token->str[j] = 0;
	return (SUCCESS);
}

static short int	fill_token(t_token *token, char *line, int *i, char **esc_quote)
{

	if (!token->export && is_export(line + *i))
		token->export = 1;
	else if (token->export)
	{
		token->export = 0;
		if (!export_quote(token, line, i, esc_quote))
			return (FAILURE);
		return (SUCCESS);
	}

// >> faut que je fasse comme export pour t_redir


	find_token_content(token, line, i);
	if (!find_token_str(token, line, i, esc_quote))
		return (FAILURE);
	return (SUCCESS);
}

static short int	fill_cmds(t_cmd *content, t_token token)
{
	t_list	*new;

	new = ft_lstnew(token.str);
	if (!new)
		return (FAILURE);
	if (token.content == _ARG)
		ft_lstadd_back(&(content->args), new);
	else if (token.content == _IN)
		ft_lstadd_back(&(content->infile), new);
	else if (token.content == _OUT)
		ft_lstadd_back(&(content->outfile), new);
	return (SUCCESS);
}

short int	tokenizing(t_exec_info *global, char *line, char **esc_quote)
{
	t_list		*tmp;
	t_states	st;
	int			i;
	int			ret;
	t_token		token;

	tmp = NULL;
	st = _START;
	ret = SUCCESS;
	init_ret_token(&token);
	i = -1;
	while (++i < (int)ft_strlen(line))
	{
		if (i == 0 || line[i] == '|')
			if (!start(&tmp, &st, line[i], &i))
				return (FAILURE);
		if (line[i] == ' ')
			i++;
		if (!fill_token(&token, line, &i, esc_quote))
			return (FAILURE);
		if (!fill_cmds(ft_lstlast(tmp)->content, token))
			return (FAILURE);
	}
	global->cmds = tmp;
	return (ret);
}
