/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/10/05 16:29:35 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *env[])
{
	char		*line;
	t_exec_info	*global;
	t_list		*tmp;

	global = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global, env))
			return (clear(&global, &line, EXIT_FAILURE));
		while (1)
		{
			line = readline(">> ");
			if (line)
			{
				// parsing
				if (!parsing(&line, &global))
					return (clear(&global, &line, EXIT_FAILURE));
				tmp = global->cmds;
				while (global->cmds)
				{
					printf("list cmds :\033[33m\n");
					print_cmds_cmd(global->cmds->content);
					global->cmds = global->cmds->next;
				}
				global->cmds = tmp;
				// exec
				clear_cmds(global->cmds);
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
	return (clear(&global, &line, EXIT_SUCCESS));
}