/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:39:16 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/18 16:06:09 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prepare_execve(char **path, char ***env, char *cmd_name, t_exec_info info)
{
	*path = get_path(cmd_name, info.env);
	if (!*path)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_COMM_NOT_FOUND);
		return (FAILURE);
	}
	*env = t_list_to_char(info.env);
	if (!*env)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_MEM);
		free(*path);
		return (FAILURE);
	}
	return (SUCCESS);
}

pid_t	launch_cmd(int i, t_list *cmd, t_run_info *run, t_exec_info info)
{
	int		res;
	pid_t	pid;

	pid = prepare_fork_pipe(i, cmd, run);
	if (pid == -2)
	{
		child((t_cmd *)cmd->content, run, info);
		return (-1);
	}
	else if (pid == 0)
	{
		child((t_cmd *)cmd->content, run, info);
		res = ft_atoi(ft_getenv_value("?", info.env));
		exit(res);
	}
	else if (pid > 0)
		parent(i, run);
	else
	{
		perror(ERR_EXEC);
		clear(info, NULL, 0);
		return (-2);
	}
	i++;
	return (pid);
}

int	dup_pipes(int pipe_dir, t_run_info *run)
{
	int	*pipe_fd;

	pipe_fd = run->left_pipe;
	if (pipe_dir == 1)
		pipe_fd = run->right_pipe;
	if (pipe_fd[pipe_dir] != -1)
	{
		if (dup2(pipe_fd[pipe_dir], pipe_dir) == -1)
			return (FAILURE);
		if (close(pipe_fd[0]) == -1)
			return (FAILURE);
		if (close(pipe_fd[1]) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
