/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:59:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 17:59:58 by lgaudet-         ###   ########.fr       */
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

static int	prep_one_heredoc(t_run_info *run, t_file_redir *redir)
{
	t_list			*elem;
	t_heredoc_info	*here;
	int				fd[2];

	here = malloc(sizeof(t_heredoc_info));
	if (!here)
		return (FAILURE);
	if (pipe(fd))
	{
		free(here);
		return (FAILURE);
	}
	elem = ft_lstnew(here);
	if (!elem)
	{
		close(fd[0]);
		close(fd[1]);
		free(here);
		return (FAILURE);
	}
	ft_lstadd_back(&run->heredocs, elem);
	heredoc_parsing(fd[1], redir->name);
	close(fd[1]);
	here->fd = fd[0];
	here->redir = redir;
	return (SUCCESS);
}

int	prep_heredocs(t_run_info *run, t_exec_info info)
{
	t_list	*cmd_head;
	t_list	*redir_head;

	cmd_head = info.cmds;
	while (cmd_head)
	{
		redir_head = ((t_cmd *)cmd_head->content)->infile;
		while (redir_head)
		{
			if (((t_file_redir *)redir_head->content)->count == _REDIR_DOUBLE)
				if (!prep_one_heredoc(run, (t_file_redir *)redir_head->content))
					return (FAILURE);
			redir_head = redir_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (SUCCESS);
}

int	heredoc(t_file_redir *redir, int real_in)
{
	int		fd[2];
	int		old_val;
	pid_t	pid;

	if (pipe(fd) || dup2(real_in, 0) == -1)
		return (FAILURE);
	old_val = g_children_running;
	g_children_running = 1;
	pid = fork();
	if (pid == 0)
	{
		g_children_running = 2;
		heredoc_parsing(fd[1], redir->name);
		exit(0);
	}
	else if (pid > 0)
		dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	if (pid < 0)
		return (FAILURE);
	waitpid(pid, NULL, 0);
	g_children_running = old_val;
	return (SUCCESS);
}
