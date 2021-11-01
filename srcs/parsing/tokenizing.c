/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 11:55:07 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_ret_token(t_token *ret_token)
{
	ret_token->export = 0;
	ret_token->str = NULL;
	ret_token->content = _ARG;
}

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

static void	find_token_content(t_token *token, char *str, int *i)
{
	if (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '<')
	{
		token->content = _IN;
		(*i)++;
	}
	else if (str[*i] == '>')
	{
		token->content = _OUT;
		(*i)++;
	}
	else
		token->content = _ARG;
	if (str[*i] == ' ')
		(*i)++;
}

static int short	find_size(char *str, int i)
{
	int		size;
	char	quote;

	size = 0;
	while (str[i] && !is_redir_space(str[i]))
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				i++;
				size++;
			}
			i++;
			continue ;
		}
		i++;
		size++;
	}
	return (size);
}

static short int	is_quote_export(char c, char **esc_quote, int loc)
{
	int	i;

	if (c == '\'' || c == '\"')
	{
		i = 0;
		if (esc_quote)
		{
			while (esc_quote[i])
			{
				if (!ft_strncmp(ft_itoa(loc), esc_quote[i], ft_strlen(esc_quote[i])))
					return (FAILURE);
				i++;
			}
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

static int short	is_export(char *line)
{
	int		i;
	char	str[7];

	i = 0;
	while (line[i] && i < 7)
	{
		str[i] = line[i];
		i++;
	}
	str[6] = 0;
	if (!ft_strncmp(str, "export", 7))
	{
		while (line[i])
		{
			if (line[i] == '=')
			{
				if (line[i + 1] && (line[i + 1] == '\"' || line[i + 1] == '\''))
					return (SUCCESS);
			}
			i++;
		}
	}
	return (FAILURE);
} 

static short int	fill_token(t_token *token, char *line, int *i, char **esc_quote)
{
	int		j;
	char	quote;

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
	token->str = malloc(sizeof(char) * find_size(line, *i) + 1);
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
