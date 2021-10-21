/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:07:20 by mballet           #+#    #+#             */
/*   Updated: 2021/10/21 17:02:31 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	find_quote(char *line, int i)
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

static int	find_size(char *line, char quote, int i)
{
	int	size;

	size = i;
	while (line[size] && line[size] != quote)
		size++;
	size++;
	while (line[size] && line[size] != quote)
		size++;
	size++;
	while (line[size] && !is_separator(line[size]))
		size++;
	size -= i;
	return (size);
}

static void	fill_in_str(char *line, char *str, int *i, int size, char quote)
{
	size = 0;
	while (line[*i] && line[*i] != quote)
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	str[size] = line[*i];
	(size)++;
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	str[size] = line[*i];
	(size)++;
	(*i)++;
	while (line[*i] && !is_separator(line[*i]))
	{
		str[size] = line[*i];
		(size)++;
		(*i)++;
	}
	str[size] = line[*i];
	(size)++;
	(*i)++;
	str[size] = 0;
}

short int	export_quote(t_cmd *content, char *line, int *i)
{
	t_list		*new;
	char		*str;
	int			size;
	char		quote;

	if (!state_default(content, line, i, 1))
		return (FAILURE);
	quote = find_quote(line, *i);
	(*i)++;
	size = find_size(line, quote, *i);
	if (!size)
		return (SUCCESS);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (FAILURE);
	fill_in_str(line, str, i, size, quote);
	if (!trim_space_export(&str))
		return (FAILURE);
	new = ft_lstnew(str);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(&(content->args), new);
	return (SUCCESS);
}