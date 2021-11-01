/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 14:29:56 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	find_token_str(t_token *token, char *line, int *i, char **esc_quote)
{
	int		j;
	char	quote;

	token->str = malloc(sizeof(char) * find_size_token(line, *i) + 1);
	if (!token->str)
		return (FAILURE);
	j = 0;
	while (line[*i] && !is_redir_space(line[*i]))
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
	(*i)--;
	return (SUCCESS);
}

static void	fill_redir(t_token *token)
{
	if (token->content.in == _SINGLE)
		token->redir->count = _REDIR_SINGLE;
	else if (token->content.in == _DOUBLE)
		token->redir->count = _REDIR_DOUBLE;
	else if (token->content.out == _SINGLE)
		token->redir->count = _REDIR_SINGLE;
	else if (token->content.out == _DOUBLE)
		token->redir->count = _REDIR_DOUBLE;
}

static short int	find_token_redir(t_token *token, char *line, int *i, char **esc_quote)
{
	int		j;
	char	quote;
	int		size;

	token->redir = malloc(sizeof(t_file_redir));
	if (!token->redir)
		return (FAILURE);
	fill_redir(token);
	if (line[*i] == ' ')
		(*i)++;
	size = find_size_token(line, *i);
	if (!size)
		return (ERR_PARSING);
	token->redir->name = malloc(sizeof(char) * size + 1);
	if (!token->redir->name)
		return (FAILURE);
	j = 0;
	while (line[*i] && line[*i] != ' ')
	{
		if (is_quote_export(line[*i], esc_quote, *i))
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
			{
				token->redir->name[j] = line[*i];
				(*i)++;
				j++;
			}
			(*i)++;
			continue ;
		}
		token->redir->name[j] = line[*i];
		(*i)++;
		j++;
	}
	token->redir->name[j] = 0;
	(*i)--;
	return (SUCCESS);
}

static short int	fill_token(t_token *token, char *line, int *i, char **esc_quote)
{
	int	ret;

	ret = SUCCESS;
	if (!token->export && is_export(line + *i))
		token->export = 1;
	else if (token->export)
	{
		token->export = 0;
		if (!export_quote(token, line, i, esc_quote))
			return (FAILURE);
		return (SUCCESS);
	}
	find_token_content(token, line, i);
	if (token->content.arg == 1)
	{
		if (!find_token_str(token, line, i, esc_quote))
			return (FAILURE);
	}
	else if (token->content.in != _NOTHING || token->content.out != _NOTHING)
	{
		ret = find_token_redir(token, line, i, esc_quote);
		if (!ret)
			return (FAILURE);
		if (ret == ERR_PARSING)
		{
			ft_fprintf(1, "syntax error near unexpected token `newline'\n");
			free(token->redir);
		}
	}
	return (ret);
}

static short int	fill_cmds(t_cmd *content, t_token token)
{
	t_list	*new;

	if (token.content.arg == 1)
	{
		new = ft_lstnew(token.str);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->args), new);
	}
	else if (token.content.in != _NOTHING)
	{
		new = ft_lstnew(token.redir);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->infile), new);
	}
	else if (token.content.out != _NOTHING)
	{
		new = ft_lstnew(token.redir);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->outfile), new);
	}
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
	i = -1;
	while (++i < (int)ft_strlen(line))
	{
		init_ret_token(&token);
		if (i == 0 || line[i] == '|')
			if (!start(&tmp, &st, line[i], &i))
				return (FAILURE);
		if (line[i] == ' ')
			i++;
		ret = fill_token(&token, line, &i, esc_quote);
		if (!ret)
			return (FAILURE);
		if (ret == ERR_PARSING)
			return (ret);
		if (!fill_cmds(ft_lstlast(tmp)->content, token))
			return (FAILURE);
	}
	global->cmds = tmp;
	return (ret);
}
