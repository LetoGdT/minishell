/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/10/08 17:24:39 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			line = readline("minishell$ ");
			if (line)
			{
				if (!parsing(&line, &global))
					return (clear(global, line, EXIT_FAILURE));
				if (line)
					free(line);
				if (!exec(global))
					return (clear(global, line, EXIT_FAILURE));
				// print_cmds(global);
				clear_cmds(global);
				global.cmds = NULL;
			}
			else
			{
				write(1, "\b\bexit\n", 7);
				break ;
			}
		}
	}
	return (EXIT_SUCCESS);
}

// suppprime fichier _trace dans libft
// >> retirer les fichiers print_cmds (printf)
