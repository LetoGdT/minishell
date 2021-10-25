/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:07:06 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/25 19:02:05 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

static int is_num(const char *str)
{
	char *s;

	s = (char *)str;
	while (*s++)
		if (!ft_isdigit(*s++))
			return (FAILURE);
	return (SUCCESS);
}

int	ft_exit(int argc, char **argv, t_list **env)
{
	long long int	status;

	(void)env;
	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, argv[0], \
		ERR_TOO_ARG);
		return (1);
	}
	printf("%s\n", EXIT_MSG);
	if (argc == 1)
		exit(PROG_SUCCESS);
	status = ft_atoll(argv[1]);
	if ((status == 0 && errno != 0) || !is_num(argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n", MINISHELL, argv[0], \
		argv[1], ERR_NUM);
		exit(255);
	}
	exit((int)status);
}
