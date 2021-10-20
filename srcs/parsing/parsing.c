/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/20 17:50:34 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

static short int	fill_env_(char *line, t_exec_info *global)
{
	int	size;
	int	i;

	size = ft_strlen(line) - 1;
	while (line[size] && !is_separator(line[size]))
	{
		size--;
	}
	global->env_ = malloc(sizeof(char) * ft_strlen(line) - size + 1);
	if (!global->env_)
		return (FAILURE);
	i = 0;
	while (line[size])
	{
		global->env_[i] = line[size];
		size++;
		i++;
	}
	global->env_[i] = 0;
	printf(">>>>>>>>>>>>>%s\n", global->env_);
	return (SUCCESS);
}

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
	if (!fill_env_(*line, global))
		return (FAILURE);
	ret = tokenizing(global, *line);
	if (!ret)
		return (FAILURE);
	// printf("line after :\033[35m%s\033[0m\n", *line);
	return (ret);
}
