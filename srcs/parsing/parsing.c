/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 15:30:52 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define ERROR_SPACE 2

short int	parsing(char **line, t_exec_info **global)
{
	short int	ret_trim_space;

	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (SUCCESS);
	printf("line before :\033[35m%s\033[0m\n", *line);
	ret_trim_space = trim_space(line);
	if (ret_trim_space == ERROR_SPACE)
		return (SUCCESS);
	if (!ret_trim_space)
		return (FAILURE);
	printf("line btw :\033[35m%s\033[0m\n", *line);
	if (!var_env(line, *global))
		return (FAILURE);
	// printf("line after :\033[35m%s\033[0m\n", *line);
	if (!tokenizing(global, *line))
		return (FAILURE);
	return (SUCCESS);
}
