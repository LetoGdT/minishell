/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/10/25 16:31:06 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

short int	parsing(char **line, t_exec_info *global)
{
	short int	ret;
	char		**esc_quote;
	int			i;

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
	// if (esc_quote)
	// {
	// 	int a = 0;
	// 	while (esc_quote[a])
	// 	{
	// 		printf("string %d :%s\n", a, esc_quote[a]);
	// 		a++;
	// 	}
	// }
	// printf("line btw :\033[35m%s\033[0m\n", *line);
	ret = tokenizing(global, *line, esc_quote);
	if (!ret)
		return (FAILURE);
	i = 0;
	if (esc_quote)
	{
		while (esc_quote[i])
		{
			if (esc_quote[i])
				free(esc_quote[i]);
			i++;
		}
		free(esc_quote);
	}
	// printf("line after :\033[35m%s\033[0m\n", *line);
	return (ret);
}

// >> je dois envoyer les esc_qupte dans is_separator