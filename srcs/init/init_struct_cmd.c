/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:56:52 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 12:16:18 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_struct_cmd(void)
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
	// if (!init_lst(&(cmd->cmd), 2))
	// 	return (NULL);
	// if (!init_lst(&(cmd->s_red_in), 2))
	// 	return (NULL);
	// if (!init_lst(&(cmd->s_red_out), 2))
	// 	return (NULL);
	// if (!init_lst(&(cmd->d_red_in), 2))
	// 	return (NULL);
	// if (!init_lst(&(cmd->d_red_out), 2))
	// 	return (NULL);
	return (cmd);
}
