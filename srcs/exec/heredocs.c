/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:59:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/12 16:19:07 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


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
		if (!heredoc_parsing(fd[1], redir))
			exit(1);
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
