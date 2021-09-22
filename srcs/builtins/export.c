/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:09:29 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 00:25:29 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	export(int argc, char **argv, t_list **env)
{
	int 	i;
	char	*res;

	i = 0;
	while (i < argc - 1)
	{
		res = ft_strchr(argv[i + 1], '=');
		if (!res)
			return (SUCCESS);
		if (res != ft_strrchr(argv[i + 1], '='))
			return (SUCCESS);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		if (!try_add(argv[i + 1], env))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
