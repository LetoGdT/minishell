/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:08:30 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 12:22:36 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int short	state_quotes(t_cmd *content, char *line, int *i, char c)
{
	int		size;
	char	*str;
	t_list	*new;

	size = 0;
	(*i)++;
	while (line[*i] && line[*i] != c)
	{
		size++;
		(*i)++;
	}
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (FAILURE);
	*i -= size;
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
