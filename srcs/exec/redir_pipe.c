/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:17:26 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/30 18:10:07 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int left_redir(t_list *cmd, t_run_info *run, t_exec_info *info)
{
	t_list	*redir_head;
	int		fd;
	int		flags;

	if (run->right_pipe[1] != -1)
	{
		if (dup2(run->right_pipe[1], 1))
			return (FAILURE);
		if (close(run->right_pipe[1]))
			return (FAILURE);
	}
	redir_head = cmd->outfile;
	while (redir_head)
	{
		if (((t_file_redir)redir_head->content)->name == _REDIR_SINGLE)
			flags = O_CREAT | O_TRUNC | O_WRONLY;
		else
			flags = O_CREAT | O_APPEND | O_WRONLY;
		fd = open(((t_file_redir)redir_head->content)->name, flags);
		if (fd < 0)
			return (FAILURE);
		if (dup2(fd, 1))
			return (FAILURE);
		if (close(fd))
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static int right_redir(t_list *cmd, t_run_info *run, t_exec_info *info)
{
	t_list	*redir_head;
	int		fd;

	if (run->left_pipe[1] != -1)
	{
		if (dup2(run->left_pipe[0], 0))
			return (FAILURE);
		if (close(run->left_pipe[0]))
			return (FAILURE);
	}
	redir_head = cmd->infile;
	while (redir_head)
	{
		fd = open((char *)redir_head->content, O_RDONLY);
		if (fd < 0)
			return (FAILURE);
		if (dup2(fd, 0))
			return (FAILURE);
		if (close(fd))
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

int prepare_redir(t_list *cmd, t_run_info *run, t_exec_info *info)
{
	if (!left_redir(cmd, run, info))
		return (FAILURE);
	if (!right_redir(cmd, run, info))
		return (FAILURE);
	return (SUCCESS);
}

int restore_io(t_run_info *run)
{
	if (dup2(0, run->fd_real_in))
		return (FAILURE);
	if (dup2(1, run->fd_real_out))
		return (FAILURE);
	return (SUCCESS);
}
