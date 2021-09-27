/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 14:30:55 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

static void	clear_cmds(t_list **cmds)
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
	if (*cmds)
		ft_lstclear(cmds, del);
}

static void	clear_env(t_list **env)
{
	if (*env)
		ft_lstclear(env, del);
}

short int	clear(t_exec_info *global, char **line, int ret)
{
	if (global)
	{
		if (global->cmds)
		{
			clear_cmds(&(global->cmds));
		}
		if (global->env)
		{
			clear_env(&(global->env));
		}
		// if (global->pids)
		// {
		// 	clear_pids(global);
		// }
		free(global);
	}
	(void)*line;
	if (*line)
		free(*line);
	return (ret);
}