/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 16:41:15 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init(t_exec_info *global, char **env)
{
	global->cmds = NULL;
	global->pids = NULL;
	global->env = NULL;
	global->env = ft_new_env(env);
	if (!global->env)
		return (FAILURE);
	return (SUCCESS);
}
