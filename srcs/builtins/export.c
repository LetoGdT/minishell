/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:09:29 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/12 18:39:09 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_name(char *str)
{
	if (!str)
		return (FAILURE);
	return (ft_isalpha(str[0]) || str[0] == '_');
}

int	ft_export(int argc, char **argv, t_list **env)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!is_valid_name(argv[i + 1]))
		{
			ft_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n", MINISHELL, argv[0], \
			argv[i + 1], ERR_IDENT);
			return (FAILURE);
		}
		if (!ft_strchr(argv[i + 1], '='))
			continue ;
		if (!try_add(argv[i + 1], env))
			return (PROG_FAILURE);
		i++;
	}
	return (PROG_SUCCESS);
}

int	ft_unset(int argc, char **argv, t_list **env)
{
	int		i;

	i = 0;
	while (i < argc - 1)
	{
		if (!argv[i + 1])
		{
			i++;
			continue ;
		}
		if (!is_valid_name(argv[i + 1]))
		{
			ft_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n", MINISHELL, argv[0], \
			argv[i + 1], ERR_IDENT);
			return (PROG_FAILURE);
		}
		ft_remove_from_env(argv[i + 1], env);
		i++;
	}
	return (PROG_SUCCESS);
}

int	ft_env(int argc, char **argv, t_list **env)
{
	t_list	*head;

	(void)argc;
	(void)argv;
	head = *env;
	while (head)
	{
		if (ft_strncmp("?", (char *)head->content, 1))
			if (!printf("%s\n", (char *)head->content))
				return (PROG_FAILURE);
		head = head->next;
	}
	return (PROG_SUCCESS);
}
