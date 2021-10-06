/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:56:52 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:46:04 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_t_cmd(void)
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

t_list	*init_content(void)
{
	t_list	*new;
	t_cmd	*cmd;

	cmd = init_t_cmd();
	if (!cmd)
		return (NULL);
	new = ft_lstnew(cmd);
	if (!new)
		return (NULL);
	return (new);
}