/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/11/07 22:05:34 by lgaudet-         ###   ########.fr       */
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
		return (clear(*global, *line, FAILURE));
	free(*line);
	if (ret != ERR_PARSING && !exec(*global))
		return (clear(*global, NULL, FAILURE));
	clear_cmds(*global);
	global->cmds = NULL;
	return (SUCCESS);
}

static short int	ctrl_d(t_exec_info *global)
{
	int res;

	res = ft_atoi(ft_getenv_value("?", global->env));
	ft_lstclear(&global->env, free);
	return (res);
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
			if (g_children_running == 3)
			{
				change_env_dollar_question(1, &global.env);
				g_children_running = 0;
			}
			if (line)
			{
				if (!minishell(&line, &global))
					return (EXIT_FAILURE);
			}
			else
				return (ctrl_d(&global));
		}
	}
	return (EXIT_SUCCESS);
}

// bug : ./minishell il dit que y a un argument '' vide
