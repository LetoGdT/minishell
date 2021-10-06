/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 14:20:48 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	if (content)
		free(content);
}

static void	clear_cmd(t_cmd *cmds)
{
	ft_lstclear(&(cmds->cmd), del);
}

void	clear_cmds(t_list *cmds)
{
	t_list	*tmp;

	tmp = cmds;
	while (cmds)
	{
		// if (((t_cmd *)((*cmds)->content))->cmd)
		// 	ft_lstclear(&(((t_cmd *)((*cmds)->content))->cmd), del);
		if (cmds->content)
			clear_cmd(cmds->content);
		
		// if (((t_cmd *)((*cmds)->content))->s_red_in)
		// 	ft_lstclear(&(((t_cmd *)((*cmds)->content))->s_red_in), del);
		// if (((t_cmd *)((*cmds)->content))->s_red_out)
		// 	ft_lstclear(&(((t_cmd *)((*cmds)->content))->s_red_out), del);
		// if (((t_cmd *)((*cmds)->content))->d_red_in)
		// 	ft_lstclear(&(((t_cmd *)((*cmds)->content))->d_red_in), del);
		// if (((t_cmd *)((*cmds)->content))->d_red_out)
		// 	ft_lstclear(&(((t_cmd *)((*cmds)->content))->d_red_out), del);
		cmds = cmds->next;
	}
	cmds = tmp;
	if (cmds)
		ft_lstclear(&cmds, del);
}

short int	clear(t_exec_info **global, char **line, int ret)
{
	if (*global)
	{
		if (((*global)->cmds))
		{
			clear_cmds((*global)->cmds);
			(*global)->cmds = NULL;
		}
		if (((*global)->env))
		{
			ft_lstclear(&((*global)->env), del);
		}
		free((*global));
	}
	if (*line)
		free(*line);
	return (ret);
}
