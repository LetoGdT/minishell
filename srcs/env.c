/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:00:19 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/16 17:06:45 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_getenv(t_list *env)
{
	t_list	*head;
	int		i;
	char	**env;

	head = env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	head = env;
	while (head)
	{
		env[i] = ft_strdup((char *)head->content);
		i++;
		head = head->next;
	}
	env[i] = NULL;
	return (env);
}

t_list	*ft_new_env(char *env[])
{
	t_list	*list;
	t_list	*head;
	int		i;

	list = ft_lstnew(NULL);
	if (!list)
		return (NULL);
	if (!env)
		return (list);
	i = 0;
	head = list;
	while (env[i])
	{
		head->next = ft_lstnew(ft_strdup(env[i]));
		if (!head->next || !head->next->content)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		i++;
		head = head->next;
	}
	head = list->next;
	free(list);
	return (head);
}

int	ft_add_to_env(char *val, t_list **env)
{
	t_list	*new_elem;

	if (!val)
		return (SUCESS);
	new_elem = ft_lstnew(ft_strdup(val));
	if (!new_elem)
		return (FAILURE);
	ft_lstadd_back(env, new_elem);
	return (SUCESS);
}

int	ft_remove_from_env(char *key, t_list **env)
{
	t_list	*head;
	t_list	*prev;

	if (!*env)
		return (FAILURE);
	head = (*env)->next;
	prev = *env;
	if (!ft_strncmp(key, (char *)(*env)->content, ft_strlen(key)))
	{
		ft_lstdelone(*env, free);
		*env = head;
		return (SUCESS);
	}
	while (head)
	{
		if (!ft_strncmp(key, (char *)head->content, ft_strlen(key)))
		{
			prev->next = head->next;
			ft_lstdelone(head, free);
			return (SUCESS);
		}
		prev = head;
		head = head->next;
	}
	return (FAILURE);
}

char	*ft_getenv_value(char *key, t_list *env)
{
	t_list	*head;
	char	*str;

	head = env;
	while (head)
	{
		str = (char *)head->content;
		if (!ft_strncmp(key, str, ft_strlen(key)))
			return (str);
		head = head->next;
	}
	return (NULL);
}