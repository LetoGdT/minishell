/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 17:34:29 by mballet          ###   ########.fr       */
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
	print_cmds(*global);
	free(*line);
	if (ret != ERR_PARSING && !exec(*global))
		return (clear(*global, NULL, EXIT_FAILURE));
	clear_cmds(*global);
	global->cmds = NULL;
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
				ft_fprintf(STDOUT_FILENO, "%s%s\n", PROMPT, EXIT_MSG);
			if (!line)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}

// suppprime fichier _trace dans libft
