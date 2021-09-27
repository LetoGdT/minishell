/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 13:57:46 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	init_cmds(t_exec_info **global)
{
	t_cmd	*cmd;

	(*global)->cmds = malloc(sizeof(t_list));
	if (!(*global)->cmds)
		return (FAILURE);
	cmd = init_struct_cmd();
	if (!cmd)
		return (FAILURE);
	(*global)->cmds = ft_lstnew(cmd);
	if (!(*global)->cmds)
		return (FAILURE);
	return (SUCCESS);
}

static short int	init_env(t_exec_info **global, char **env)
{
	(*global)->env = ft_new_env(env);
	if (!(*global)->env)
		return (FAILURE);
	return (SUCCESS);
}

short int	init(t_exec_info **global, char **env)
{
	*global = malloc(sizeof(t_exec_info));
	if (!(*global))
		return (FAILURE);
	if (!init_cmds(global))
		return (FAILURE);
	if (!init_env(global, env))
		return (FAILURE);
	return (SUCCESS);
}
