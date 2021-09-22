/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 20:08:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 00:27:55 by lgaudet-         ###   ########.fr       */
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
	char	**token_list;
	int		res;

	token_list = ft_split(str, '=');
	if (token_list == NULL)
		return (FAILURE);
	key = token_list[0];
	val = token_list[1];
	if (!val)
		val = ft_strdup("");
	if (!val)
		return (FAILURE);
	free(token_list);
	token_list = ft_getenv_value(key, *env);
	if (token_list != NULL)
	{
		free(*token_list);
		*token_list = ft_strdup(val);
		res = *token_list == NULL;
	}
	else
		res = ft_add_to_env(str, env);
	free(str);
	free(key);
	free(val);
	return (res);
}
