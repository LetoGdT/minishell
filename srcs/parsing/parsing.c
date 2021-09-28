/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/09/28 17:20:15 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	fill_in_cmds(char **line, t_exec_info **global)
{
	int	i;

	i = 0;
	while((*line)[i])
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\'' && (*line)[i] != '\"')
		{
			// split de ' ' et '\'' et '\"' mais faut que ce soit dans le bonne ordre..
		}
		i++;
	}
	return (SUCCESS);
}

short int	parsing(char **line, t_exec_info **global)
{
	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	printf("line before :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, *global))
		return (FAILURE);
	printf("line after :\033[35m%s\033[0m\n", *line);
	if (!fill_in_cmds(line, global))
		return (FAILURE);
	return (SUCCESS);
}
