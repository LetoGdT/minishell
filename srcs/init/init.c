/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 14:40:09 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init(t_exec_info **global, char **env)
{
	*global = malloc(sizeof(t_exec_info));
	if (!(*global))
		return (FAILURE);
	(*global)->cmds = NULL;
	(*global)->pids = NULL;
	(*global)->env = NULL;
	// if (!init_cmds(global))
	// 	return (FAILURE);
	(*global)->env = ft_new_env(env);
	if (!(*global)->env)
		return (FAILURE);
	return (SUCCESS);
}
