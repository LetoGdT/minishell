/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:17:26 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/15 18:04:49 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	right_redir(t_cmd *cmd, t_run_info *run)
{
	t_list	*redir_head;
	int		fd;
	int		flags;

	if (!dup_pipes(1, run))
		return (FAILURE);
	redir_head = cmd->outfile;
	while (redir_head)
	{
		if (((t_file_redir *)redir_head->content)->count == _REDIR_SINGLE)
			flags = O_CREAT | O_TRUNC | O_WRONLY;
		else
			flags = O_CREAT | O_APPEND | O_WRONLY;
		fd = open(((t_file_redir *)redir_head->content)->name, flags, 0644);
		if (fd < 0)
			return (FAILURE);
		if (dup2(fd, 1) == -1)
			return (FAILURE);
		if (close(fd))
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static int	left_redir(t_cmd *cmd, t_run_info *run)
{
	t_list	*redir_head;
	int		fd;

	if (!dup_pipes(0, run))
		return (FAILURE);
	redir_head = cmd->infile;
	while (redir_head)
	{
		if (((t_file_redir *)redir_head->content)->count == _REDIR_DOUBLE)
		{
			if (!heredoc((t_file_redir *)redir_head->content))
				return (FAILURE);
			redir_head = redir_head->next;
			continue ;
		}
		fd = open((char *)redir_head->content, O_RDONLY);
		if (fd < 0)
			return (FAILURE);
		if (dup2(fd, 0) == -1)
			return (FAILURE);
		if (close(fd) == -1)
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

int	prepare_redir(t_cmd *cmd, t_run_info *run)
{
	if (!left_redir(cmd, run))
		return (FAILURE);
	if (!right_redir(cmd, run))
		return (FAILURE);
	return (SUCCESS);
}

int	restore_io(t_run_info *run)
{
	if (dup2(0, run->fd_real_in) == -1)
		return (FAILURE);
	if (dup2(1, run->fd_real_out) == -1)
		return (FAILURE);
	return (SUCCESS);
}

pid_t	prepare_fork_pipe(int rank, t_list *head, t_run_info *run)
{
	if (head->next != NULL)
	{
		if (pipe(run->right_pipe))
			return (-1);
	}
	else
		run->right_pipe[1] = -1;
	if (head->next == NULL && rank == 0 && \
		!builtin_get_default_fork((char *) \
		((t_cmd *)head->content)->args->content))
		return (-2);
	g_children_running = 1;
	return (fork());
}
