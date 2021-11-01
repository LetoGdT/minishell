/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:04:35 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 12:16:12 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ret_token(t_token *ret_token)
{
	ret_token->export = 0;
	ret_token->str = NULL;
	ret_token->content = _ARG;
}

void	find_token_content(t_token *token, char *str, int *i)
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