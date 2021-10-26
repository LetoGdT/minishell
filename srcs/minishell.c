/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 17:12:34 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_children_running;

// static short int	minishell()
// {
	
// 	return (SUCCESS);
// }

int	main(int argc, char **argv, char *env[])
{
	char		*line;
	t_exec_info	global;
	int			ret;

	line = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global, env))
			return (clear(global, line, EXIT_FAILURE));
		while (1)
		{
			// if (!minishell(&line, &global))
			// 	return (FAILURE);
			line = readline(PROMPT);
			if (line)
			{
				add_history(line);
				ret = parsing(&line, &global);
				if (!ret)
					return (clear(global, line, EXIT_FAILURE));
				print_cmds(global);
				free(line);
				if (ret != ERR_PARSING && !exec(global))
					return (clear(global, NULL, EXIT_FAILURE));
				clear_cmds(global);
				global.cmds = NULL;
			}
			else
			{
				ft_fprintf(STDOUT_FILENO, "%s%s\n", PROMPT, EXIT_MSG);
				break ;
			}
		}
	}
	return (EXIT_SUCCESS);
}

// >> retirer les fichiers print_cmds (printf)