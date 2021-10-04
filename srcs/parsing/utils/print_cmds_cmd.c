/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:36:37 by mballet           #+#    #+#             */
/*   Updated: 2021/10/04 16:01:32 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds_cmd(t_list *cmds, t_cmd *content)
{
	t_list	*temp;

	temp = cmds;
	if (!cmds)
	{
		printf("list cmds n'existe pas\n");
		return ;
	}
	printf("list cmds :\033[33m\n");
	while (cmds)
	{
		printlst_str(content->cmd);
		cmds = cmds->next;
	}
	printf("\033[0m");
	cmds = temp;
}