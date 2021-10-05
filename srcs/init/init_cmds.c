/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:56:52 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 16:49:30 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_struct_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	return (cmd);
}

short int	init_cmds(t_list **cmds)
{
	t_list	*tmp;
	t_cmd	*cmd;

	cmd = init_struct_cmd();
	if (!cmd)
		return (FAILURE);
	tmp = ft_lstnew(cmd);
	if (!tmp)
		return (FAILURE);
	// (*cmds) = ft_lstnew(cmd);
	// if (!(*cmds))
	// 	return (FAILURE);
	// cmds = tmp;
	ft_lstadd_back(cmds, tmp);
	return (SUCCESS);
}