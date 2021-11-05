/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:24:49 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/05 18:22:46 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(int argc, char **argv, t_list **env)
{
	int	i;
	int	is_newline;

	(void)env;
	i = 1;
	if (argc > 1 && !ft_strncmp(argv[i], "-n", 2))
	{
		is_newline = 0;
		i++;
		while (!ft_strncmp(argv[i], "-n", 2))
			i++;
	}
	else
		is_newline = 1;
	while (i < argc - 1)
	{
		printf("%s ", argv[i]);
		i++;
	}
	if (argc - i > 0)
		printf("%s", argv[argc - 1]);
	if (is_newline)
		printf("\n");
	return (PROG_SUCCESS);
}
