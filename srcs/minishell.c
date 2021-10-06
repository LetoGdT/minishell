/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 17:39:23 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *env[])
{
	char		*line;
	t_exec_info	*global;
	// t_list		*tmp;

	global = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global, env))
			return (clear(global, &line, EXIT_FAILURE));
		while (1)
		{
			line = readline("minishell$ ");
			if (line)
			{
				if (!parsing(&line, &global))
					return (clear(global, &line, EXIT_FAILURE));
				// exec
				// print_cmd(global);
				clear_cmds(global);
				global->cmds = NULL;
				if (line)
					free(line);
			}
			else
			{
				write(1, "\b\bexit\n", 7);
				break ;
			}
		}
	}
	return (clear(global, &line, EXIT_SUCCESS));
}


// suppprime fichier _trace dans libft
// >> retirer les fichiers print_cmds (printf)