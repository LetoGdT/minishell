/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:17:09 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 11:01:24 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_exec_info *global)
{
	t_list		*tmp;

	tmp = global->cmds;
	while (global->cmds)
	{
		printf("list cmds :\033[33m\n");
		print_cmds_cmd(global->cmds->content);
		global->cmds = global->cmds->next;
	}
	global->cmds = tmp;
}