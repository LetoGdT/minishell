/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/09/23 11:46:20 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	init_cmds(t_exec_info **global)
{
	t_cmd	*cmds;

	cmds = init_struct_cmd();
	if (!cmds)
		return (FAILURE);
	(*global)->cmds = ft_lstnew(cmds);
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
