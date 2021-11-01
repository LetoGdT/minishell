/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 12:08:03 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_children_running;

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
			line = readline(PROMPT);
			if (line)
			{
				add_history(line);
				ret = parsing(&line, &global);
				if (!ret)
					return (clear(global, line, EXIT_FAILURE));
				// print_cmds(global);
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
			// rl_on_new_line();
		}
	}
	return (EXIT_SUCCESS);
}

// suppprime fichier _trace dans libft
// >> retirer les fichiers print_cmds (printf)


// >> parfois y a des bug ou j'ai ma chaine line qui a pas de \0 j'ai l'impression