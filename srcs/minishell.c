/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/09/23 14:25:04 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *env[])
{
	char		*line;
	t_exec_info	*global;		// Faut qu'on la mette en global

	global = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global, env))
			return (clear(global, &line, EXIT_FAILURE));
		while (1)
		{
			line = readline(">> ");
			if (line)
			{
				// parsing
				if (!parsing(line, &global))
					return (clear(global, &line, EXIT_FAILURE));
				// printf("line :%s\n", line);
				// exec
				if (line)
					free(line);
			}
			else
			{
				printf("exit\n");
				break ;
			}
		}
	}
	return (clear(global, &line, EXIT_SUCCESS));
}
