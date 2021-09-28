/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/09/28 14:49:02 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static short int	treat_special_state(char *line, t_exec_info **global)
// {
// 	(void)line;
// 	(void)global;
// 	int	i;
	
// 	i = 0;
// 	if (line[i] == '\'')
// 	{
// 		i += !state_s_quote(line, global);
// 	}
// 	else if (line[i] == '\"')
// 	{
// 		i += !state_d_quote(line, global);
// 	}
// 	return (i);
// }

short int	parsing(char **line, t_exec_info **global)
{
	// int	i;
	// int	save;

	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	printf("line before :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, *global))
		return (FAILURE);
	printf("line after :\033[35m%s\033[0m\n", *line);
	// i = 0;
	// while(line[i])
	// {
	// 	save = i;
	// 	if (is_special_state(line[i]))
	// 	{
	// 		i += treat_special_state(line + i, global);
	// 		if (i < save)
	// 			return (FAILURE);
	// 	}
	// 	else
	// 	{
			
	// 	}
	// 	i++;
	// }
	// printf("line end :\033[35m%s\033[0m\n", *line);
	return (SUCCESS);
}
