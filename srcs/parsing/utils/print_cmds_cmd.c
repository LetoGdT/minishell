/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:36:37 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:36:02 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds_cmd(t_cmd *content)
{
	t_list	*tmp;
	
	tmp = content->cmd;
	while (tmp)
	{
		// printlst_str(tmp);
		printf("%s, ", tmp->content);
		tmp = tmp->next;
	}
	printf("\n\033[0m");
}