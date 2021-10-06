/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:17:09 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:35:07 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_exec_info *global)
{
	t_list		*tmp;

	if (!(global->cmds))
	{
		printf("list empty\n");
		return ;
	}
	tmp = global->cmds;
	while (tmp)
	{
		printf("list cmds :\033[33m\n");
		print_cmds_cmd(tmp->content);
		tmp = tmp->next;
	}
}