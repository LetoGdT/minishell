/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 14:43:53 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	parsing(char **line, t_exec_info **global)
{
	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	// printf("line before :\033[35m%s\033[0m\n", *line);
	if (!trim_space(line))
		return (FAILURE);
	// printf("line btw :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, *global))
		return (FAILURE);
	// printf("line after :\033[35m%s\033[0m\n", *line);
	if (!tokenizing(global, *line))
		return (FAILURE);
	return (SUCCESS);
}
