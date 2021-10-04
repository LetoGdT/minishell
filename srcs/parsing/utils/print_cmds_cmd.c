/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:36:37 by mballet           #+#    #+#             */
/*   Updated: 2021/09/30 16:44:10 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds_cmd(t_exec_info *global)
{
	t_list	*temp;

	temp = global->cmds;
	printf("list cmds :\033[33m\n");
	while (global->cmds)
	{
		printlst_str(global->cmds->content);
		global->cmds = global->cmds->next;
	}
	printf("\033[0m");
	global->cmds = temp;
}