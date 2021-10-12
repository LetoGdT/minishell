/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:33:47 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/12 17:54:25 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**t_list_to_char(t_list *lst)
{
	t_list	*head;
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	head = lst;
	i = 0;
	while (head)
	{
		res[i] = ft_strdup((char *)head->content);
		if (!res[i])
		{
			ft_free_token_list(res);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	wait_children(pid_t last_child, int *stat_loc)
{
	g_children_running = 0;
	waitpid(last_child, stat_loc, 0);
	while (wait(NULL) != -1)
		;
}

int		init_exec(t_run_info *run)
{
	run->fd_real_in = dup(0);
	run->fd_real_out = dup(1);
	run->left_pipe[0] = -1;
	run->left_pipe[1] = -1;
	if (run->fd_real_out == -1 || run->fd_real_in == -1)
	{
		perror(ERR_EXEC);
		return (FAILURE);
	}
	return (SUCCESS);
}
