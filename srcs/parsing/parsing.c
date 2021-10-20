/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/20 17:31:20 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

short int	parsing(char **line, t_exec_info *global)
{
	short int	ret;

	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	// printf("line before :\033[35m%s\033[0m\n", *line);
	ret = trim_space(line);
	if (ret == ERROR_SPACE)
		return (SUCCESS);
	if (!ret)
		return (FAILURE);
	// printf("line btw :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, global))
		return (FAILURE);
	// printf("line after :\033[35m%s\033[0m\n", *line);
	ret = tokenizing(global, *line);
	if (!ret)
		return (FAILURE);
	return (ret);
}
