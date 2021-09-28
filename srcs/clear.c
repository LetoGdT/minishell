/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/09/28 08:53:25 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	if (content)
		free(content);
}

static void	clear_cmds(t_list **cmds)
{
	t_list	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (((t_cmd *)((*cmds)->content))->cmd)
		{
			ft_lstclear(&(((t_cmd *)((*cmds)->content))->cmd), del);
		}
		if (((t_cmd *)((*cmds)->content))->infile)
		{
			ft_lstclear(&(((t_cmd *)((*cmds)->content))->infile), del);
		}
		if (((t_cmd *)((*cmds)->content))->outfile)
		{
			ft_lstclear(&(((t_cmd *)((*cmds)->content))->outfile), del);
		}
		tmp = tmp->next;
	}
	if (*cmds)
		ft_lstclear(cmds, del);
}

short int	clear(t_exec_info **global, char **line, int ret)
{
	if (*global)
	{
		if ((*global)->cmds)
		{
			clear_cmds(&((*global)->cmds));
		}
		if ((*global)->env)
		{
			ft_lstclear(&((*global)->env), del);
		}
		// if ((*global)->pids)
		// {
		// 	clear_pids((*global));
		// }
		free((*global));
	}
	if (*line)
		free(*line);
	return (ret);
}