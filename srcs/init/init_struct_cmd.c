/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:56:52 by mballet           #+#    #+#             */
/*   Updated: 2021/09/22 16:45:30 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	init_lst(t_list **lst)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (FAILURE);
	str[0] = '0';
	str[1] = 0;
	*lst = ft_lstnew(str);
	if (!(*lst))
		return (FAILURE);
	return (SUCCESS);
}

t_cmd	*init_struct_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!init_lst(&(cmd->cmd)))
		return (NULL);
	if (!init_lst(&(cmd->infile)))
		return (NULL);
	if (!init_lst(&(cmd->outfile)))
		return (NULL);
	return (cmd);
}