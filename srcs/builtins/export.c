/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:09:29 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 19:30:28 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export(int argc, char **argv, t_list **env)
{
	int 	i;
	char	*is_valid;

	i = 0;
	while (i < argc - 1)
	{
		is_valid = ft_strchr(argv[i + 1], '=');
		if (is_valid && !try_add(argv[i + 1], env))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	unset(int argc, char **argv, t_list **env)
{
	int		i;
	char	*key;

	i = 0;
	while (i < argc - 1)
	{
		if (!argv[i + 1])
		{
			i++;
			continue ;
		}
		ft_remove_from_env(argv[i + 1], env);
		free(argv[i + 1]);
		i++;
	}
	return (SUCCESS);
}

int	env(int argc, char **argv, t_list **env)
{
	t_list	*head;

	(void)argc;
	(void)argv;
	head = *env;
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
	return (SUCCESS);
}
