/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:56:52 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 16:02:27 by mballet          ###   ########.fr       */
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
	cmd->s_red_in = NULL;
	cmd->s_red_out = NULL;
	cmd->d_red_in = NULL;
	cmd->d_red_out = NULL;
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