/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:38:16 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 16:06:02 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int short	state_default(t_cmd *cmds, char *line, int *i)
{
	t_list	*new;
	char	*str;
	int		size;

	size = *i;
	while (line[size] && !is_separator(line[size]))
		size++;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (FAILURE);
	size = 0;
	while (line[*i] && !is_separator(line[*i]))
	{
		str[size] = line[*i];
		size++;
		(*i)++;
	}
	str[size] = 0;
	new = ft_lstnew(str);
	ft_lstadd_back(&(cmds->cmd), new);
	return (SUCCESS);
}
