/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 11:37:26 by mballet          ###   ########.fr       */
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

short int	parsing(char *line, t_exec_info **global)
{
	// int	i;
	// int	save;

	if (line && line[0] == 0)
		return (SUCCESS);
//	>>Erreurs basiques
	if (!basic_errors(line))
		return (SUCCESS);
	(void)global;
	// i = 0;
//	>>Je remplace tous les $ par leur valeur sauf quand ''
	printf("line before :\033[35m%s\033[0m\n", line);
	if (!line_without_dollar(&line, *global))
		return (FAILURE);
	printf("line after :\033[35m%s\033[0m\n", line);

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
	// change state -regular/dollar/s_quote/d_quote
	return (SUCCESS);
}
