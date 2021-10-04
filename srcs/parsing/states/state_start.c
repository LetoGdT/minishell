/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:07:30 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 16:09:48 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int short	state_start(t_cmd *cmds, char *line, int *i)
{
	t_list	*new;
	char	*str;
	int		size;

	cmds = init_cmds();
	if (!cmds)
		return (FAILURE);
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

//	check if command correspond a un truc valide
//	if probleme je dois free str
	
	new = ft_lstnew(str);
	ft_lstadd_back(&(cmds->cmd), new);
	return (SUCCESS);
}