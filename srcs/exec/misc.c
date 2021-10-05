/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:33:47 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/05 21:19:31 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **t_list_to_char(t_list *lst)
{
	t_list	*head;
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	head = lst;
	i = 0;
	while (lst)
	{
		res[i] = ft_strdup((char *)head->content);
		if (!res[i])
		{
			free_token_list(res);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void wait_children(pid_t last_child, int *stat_loc, int nb_of_children)
{
	int	i;

	waitpid(last_child, stat_loc, 0);
	i = 0;
	while (i < nb_of_children - 1)
		waitpid(-1, NULL, 0);
}
