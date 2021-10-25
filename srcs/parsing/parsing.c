/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/25 18:19:39 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

short int	parsing(char **line, t_exec_info *global)
{
	short int	ret;
	char		**esc_quote;

	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (ERROR_SPACE);
	// printf("line before :\033[35m%s\033[0m\n", *line);
	ret = trim_space(line);
	if (ret == ERROR_SPACE)
		return (SUCCESS);
	if (!ret)
		return (FAILURE);
	esc_quote = NULL;
	if (!var_env(line, global, &esc_quote))
		return (FAILURE);
	// printf("line btw :\033[35m%s\033[0m\n", *line);
	ret = tokenizing(global, *line, esc_quote);
	if (!ret)
		return (FAILURE);
	// printf("line after :\033[35m%s\033[0m\n", *line);
	return (ret);
}
