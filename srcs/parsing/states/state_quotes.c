/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:08:30 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 16:11:21 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_size(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

int short	state_quotes(t_cmd *content, char *line, int *i, char c)
{
	int		size;
	char	*str;
	t_list	*new;

	(*i)++;
	size = find_size(line, *i, c);
	if (!size)
		return (SUCCESS);
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (FAILURE);
	size = 0;
	while (line[*i] && line[*i] != c)
	{
		str[size] = line[*i];
		size++;
		(*i)++;
	}
	str[size] = 0;
	new = ft_lstnew(str);
	ft_lstadd_back(&(content->args), new);
	if (line[*i + 1] == ' ')
		(*i)++;
	return (SUCCESS);
}
