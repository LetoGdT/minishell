/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:59:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/14 20:32:18 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	heredoc_parsing(int fd, char *str)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("");
		if (line)
		{
			if (!ft_strncmp(line, str, ft_strlen(str)))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(str, fd);
			free(line);
		}
		else
			break ;
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
