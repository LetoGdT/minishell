/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:09:29 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/24 22:27:02 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_export(int argc, char **argv, t_list **env)
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
		ft_remove_from_env(argv[i + 1], env);
		i++;
	}
	return (SUCCESS);
}

int	ft_env(int argc, char **argv, t_list **env)
{
	t_list	*head;

	(void)argc;
	(void)argv;
	head = *env;
	while (head)
	{
		if (!printf("%s\n", (char *)head->content))
			return (FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}
