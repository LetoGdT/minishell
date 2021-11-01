/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:07:20 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 11:59:09 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	find_equal(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '=' && line[i + 1])
			break ;
		i++;
	}
	if (line[i + 1])
		return (line[i + 1]);
	else
		return (line[i]);
}

int short	is_export_quote(char *line)
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

static int	find_size(char *line, char quote, int i, char **esc_quote)
{
	int	size;

	size = i;
	while (line[size] && line[size] != quote)
		size++;
	size++;
	while (line[size] && line[size] != quote)
		size++;
	size++;
	while (line[size] && !is_separator(line[size], esc_quote, size))
		size++;
	size -= i - 2;
	return (size);
}

static void	fill_in_str(char *line, char *str, int *i, int size, char quote, char **esc_quote)
{
	size = 0;
	while (line[*i] && line[*i] != quote)
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	(*i)++;
	while (line[*i] && !is_separator(line[*i], esc_quote, *i))
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	str[size] = line[*i];
	str[size] = 0;
}

short int	export_quote(t_token *token, char *line, int *i, char **esc_quote)
{
	int			size;
	char		quote;

	quote = find_equal(line, *i);
	size = find_size(line, quote, *i, esc_quote);
	if (!size)
		return (SUCCESS);
	token->str = malloc(sizeof(char) * size + 1);
	if (!token->str)
		return (FAILURE);
	fill_in_str(line, token->str, i, size, quote, esc_quote);
	return (SUCCESS);
}