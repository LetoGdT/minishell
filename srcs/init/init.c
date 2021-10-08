/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 20:01:14 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init(t_exec_info *global, char **env)
{
	if (signal(SIGINT, sig_int) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "%s\n", ERR_SIGINT);
	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "%s\n", ERR_SIGQUIT);
	global->cmds = NULL;
	global->pids = NULL;
	global->env = NULL;
	global->env = ft_new_env(env);
	if (!global->env)
		return (FAILURE);
	g_children_running = 0;
	return (SUCCESS);
}
