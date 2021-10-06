/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:33:44 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	if (content)
	{
		print_cmds_cmd(((t_cmd *)content));
		ft_lstclear(&(((t_cmd *)content)->cmd), free);
		print_cmds_cmd(((t_cmd *)content));
		free(content);
	}
}

// static void	clear_cmd(t_cmd *cmds)
// {
// 	ft_lstclear(&(cmds->cmd), del);
// }

void	clear_cmds(t_exec_info *global)
{
	// t_list	*tmp;

	// printf("clear in the loop\n");
	// tmp = global->cmds;
	// while (global->cmds)
	// {
	// 	if (global->cmds->content)
	// 		clear_cmd(global->cmds->content);
	// 	global->cmds = global->cmds->next;
	// }
	// global->cmds = tmp;
	if (global->cmds)
		ft_lstclear(&global->cmds, del);
}

short int	clear(t_exec_info *global, char **line, int ret)
{
	// printf("clear at the end 1\n");
	if (global)
	{
		// printf("clear at the end 2\n");
		if ((global->cmds))
		{
			// printf("clear at the end 3\n");
			clear_cmds(global);
		}
		if ((global->env))
		{
			ft_lstclear(&(global->env), free);
		}
		free(global);
	}
	if (*line)
		free(*line);
	return (ret);
}
