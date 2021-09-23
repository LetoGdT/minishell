/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:24:49 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 21:39:36 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo(int argc, char **argv, t_list **env)
{
	int	i;
	int	is_newline;

	(void)env;
	if (argc > 1 && !ft_strncmp(argv[1], "-n", 3))
	{
		i = 1;
		is_newline = 0;
	}
	else
	{
		is_newline = 1;
		i = 0;
	}
	while (i < argc - 2)
	{
		printf("%s ", argv[i + 1]);
		i++;
	}
	printf("%s", argv[argc - 1]);
	if (is_newline)
		printf("\n");
	return (SUCESS);
}
