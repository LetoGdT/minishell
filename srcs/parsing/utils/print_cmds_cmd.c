/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:36:37 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 16:11:27 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds_cmd(t_cmd *content)
{
	while (content->cmd)
	{
		// printlst_str(content->cmd);
		printf("%s, ", content->cmd->content);
		content->cmd = content->cmd->next;
	}
	printf("\n\033[0m");
}