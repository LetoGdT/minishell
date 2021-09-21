/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 17:08:01 by mballet           #+#    #+#             */
/*   Updated: 2021/09/21 14:19:53 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char		*line;
	t_exec_info	*global;		// Faut qu'on la mette en global

	global = NULL;
	if (argc > 1 || argv[1])
		write(1, "Wrong numbers of arguments\n", 27);
	else
	{
		if (!init(&global))
			return (clear(global, FAILURE));
		while (1)
		{
			line = readline(">>  ");
			if (line)
			{
				// parsing
				if (!parsing(line))
					return (clear(global, FAILURE));
				// printf("line :%s\n", line);
				// exec
				free(line);
			}
			else
			{
				printf("exit\n");
				break ;
			}
		}
	}
	return (clear(global, SUCCESS));
}
