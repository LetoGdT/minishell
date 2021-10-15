/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:59:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/15 15:24:12 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_putstr_fd_list(t_list *list, int fd)
{
	t_list	*head;

	head = list;
	while (head)
	{
		ft_putstr_fd((char *)head->content, fd);
		ft_putstr_fd("\n", fd);
		head = head->next;
	}
	ft_lstclear(&list, free);
}

static int	ft_lstadd_back_char(char *str, t_list **list)
{
	t_list	*elem;

	elem = ft_lstnew(str);
	if (!elem)
	{
		ft_lstclear(list, free);
		return (FAILURE);
	}
	ft_lstadd_back(list, elem);
	return (SUCCESS);
}

static void	heredoc_parsing(int fd, char *str)
{
	char	*line;
	t_list	*list;

	list = NULL;
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (line)
		{
			if (!ft_strncmp(line, str, ft_strlen(str)))
			{
				free(line);
				ft_putstr_fd_list(list, fd);
				return ;
			}
			if (!ft_lstadd_back_char(line, &list))
				return ;
		}
		else
			return ;
	}
}

int	heredoc(t_file_redir *redir)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd))
		return (FAILURE);
	g_children_running = 1;
	pid = fork();
	if (pid == 0)
	{
		heredoc_parsing(fd[1], redir->name);
		exit(0);
	}
	else if (pid > 0)
		dup2(fd[0], 0);
	else
	{
		close(fd[0]);
		close(fd[1]);
		return (FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	return (SUCCESS);
}
