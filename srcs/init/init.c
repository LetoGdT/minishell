/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/09/21 14:19:29 by mballet          ###   ########.fr       */
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
	// global->cmds = ft_lstnew((void *)link);
	if (!(*global)->cmds)
		return (FAILURE);
	return (SUCCESS);
}

short int	init(t_exec_info **global)
{
	*global = malloc(sizeof(t_exec_info));
	if (!(*global))
		return (FAILURE);
	if (!init_cmds(global))
		return (FAILURE);
	return (SUCCESS);
}
