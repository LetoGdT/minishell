/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 20:08:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 18:15:28 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_add_to_env(char *val, t_list **env)
{
	t_list	*new_elem;

	if (!val)
		return (SUCCESS);
	new_elem = ft_lstnew(ft_strdup(val));
	if (!new_elem)
		return (FAILURE);
	ft_lstadd_back(env, new_elem);
	return (SUCCESS);
}

int try_add(char *str, t_list **env)
{
	char	*key;
	char	*val;
	char	**env_val;
	int		res;

	key = str;
	val = ft_strchr(str, '=');
	if (!val)
		return (FAILURE);
	*val = '\0';
	val++;
	env_val = ft_getenv_value(key, *env);
	if (env_val != NULL)
	{
		free(*env_val);
		*env_val = ft_strdup(val);
		res = *env_val == NULL;
	}
	else
		res = ft_add_to_env(str, env);
	free(str);
	return (res);
}
