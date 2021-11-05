/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/11/05 18:07:05 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_children_running;

static short int	minishell(char **line, t_exec_info *global)
{
	int	ret;

	add_history(*line);
	ret = parsing(line, global);
	if (!ret)
		return (clear(*global, *line, EXIT_FAILURE));
	free(*line);
	if (ret != ERR_PARSING && !exec(*global))
		return (clear(*global, NULL, EXIT_FAILURE));
	clear_cmds(*global);
	global->cmds = NULL;
	return (SUCCESS);
}

static short int	ctrl_d(t_exec_info *global)
{
	char	*line;

	line = ft_strdup("exit");
	if (!line)
		return (FAILURE);
	if (!minishell(&line, global))
		return (FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv, char *env[])
{
	char		*line;
	t_exec_info	global;

	line = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global, env))
			return (clear(global, line, EXIT_FAILURE));
		while (1)
		{
			line = readline(PROMPT);
			if (line)
			{
				if (!minishell(&line, &global))
					return (FAILURE);
			}
			else
				if (!ctrl_d(&global))
					return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

// bug : ./minishell il dit que y a un argument '' vide
