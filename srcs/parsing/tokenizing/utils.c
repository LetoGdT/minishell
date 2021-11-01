/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:04:35 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 14:24:32 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start(t_list **tmp, t_states *st, char c, int *i)
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

void	init_ret_token(t_token *ret_token)
{
	ret_token->export = 0;
	ret_token->str = NULL;
	ret_token->redir = NULL;
	ret_token->content.arg = 0;
	ret_token->content.in = _NOTHING;
	ret_token->content.out = _NOTHING;
}

void	find_token_content(t_token *token, char *str, int *i)
{
	if (str[*i] == ' ')
		(*i)++;
	if (str[*i] && str[*i] == '<')
	{
		token->content.in = _SINGLE;
		if (str[*i + 1] && str[*i + 1] == '<')
		{
			token->content.in = _DOUBLE;
			(*i)++;
		}
		(*i)++;
	}
	else if ( str[*i] && str[*i] == '>')
	{
		token->content.out = _SINGLE;
		if (str[*i + 1] && str[*i + 1] == '>')
		{
			token->content.out = _DOUBLE;
			(*i)++;
		}
		(*i)++;
	}
	else
		token->content.arg = 1;
	if (str[*i] == ' ')
		(*i)++;
}

int short	find_size_token(char *str, int i)
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

short int	is_quote_export(char c, char **esc_quote, int loc)
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