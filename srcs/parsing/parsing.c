/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 13:59:50 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static short int	fill_in_cmds(char **line, t_exec_info **global)
// {
// 	int	i;

// 	i = 0;
// 	while((*line)[i])
// 	{
// 		if ((*line)[i] == '|')
// 		{
// 			if (i == 0)
// 			{
// 				write (1, "syntax error near unexpected token `|'\n", 39);
// 				return ()
// 			}
// 		}
// 		if ((*line)[i] != ' ' && (*line)[i] != '\'' && (*line)[i] != '\"')
// 		{
// 			// split de ' ' et '\'' et '\"' mais faut que ce soit dans le bonne ordre..
// 		}
// 		i++;
// 	}
// 	return (SUCCESS);
// }

short int	parsing(char **line, t_exec_info **global)
{
	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	printf("line before :\033[35m%s\033[0m\n", *line);
	if (!trim_space(line))
		return (FAILURE);
	printf("line btw :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, *global))
		return (FAILURE);
	printf("line after :\033[35m%s\033[0m\n", *line);
	if (!tokenizing(*global, *line))
		return (FAILURE);
	// printf("line end :\033[35m%s\033[0m\n", *line);
	return (SUCCESS);
}
