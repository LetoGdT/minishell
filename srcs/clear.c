/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 16:45:18 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	if (content)
	{
		ft_lstclear(&(((t_cmd *)content)->cmd), free);
		ft_lstclear(&(((t_cmd *)content)->infile), free);
		ft_lstclear(&(((t_cmd *)content)->outfile), free);
		free(content);
	}
}

void	clear_cmds(t_exec_info global)
{
	if (global.cmds)
		ft_lstclear(&(global.cmds), del);
}

short int	clear(t_exec_info global, char *line, int ret)
{
	if ((global.cmds))
	{
		clear_cmds(global);
	}
	if ((global.env))
	{
		ft_lstclear(&(global.env), free);
	}
	if (line)
		free(line);
	return (ret);
}
