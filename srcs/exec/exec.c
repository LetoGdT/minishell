/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/30 19:05:51 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec(t_exec_info *info)
{
	t_list		*head;
	t_run_info	run;
	pid_t		pid;
	int			i;

	run.fd_real_in = dup(0);
	run.fd_real_out = dup(1);
	run.left_pipe[0] = -1;
	if (run.fd_real_out == -1 || run.fd_real_in == -1)
	{
		perror(ERR_EXEC);
		return (FAILURE);
	}
	cmds_head = info->cmds;
	i = 0;
	while (cmds_head)
	{
		if (cmds_head != NULL)
		{
			if (pipe(run->right_pipe))
				return (FAILURE);
		}
		else
			run->right_pipe[1] = -1;
		pid = fork();
		if (pid == 0)
		{
			if (!prepare_redir(cmds_head, &run, info))
				return (FAILURE);
			if (!launch_prog(cmds_head, info))
				return (FAILURE);
			if (!restore_io(&run))
				return (FAILURE);
			return (SUCCESS);
		}
		if (pid > 0)
		{
			if (i != 0)
			{
				close(run.left_pipe[0]);
				close(run.left_pipe[1]);
			}
			run.left_pipe[0] = run.right_pipe[0];
		}
		else
		{
			perror(ERR_EXEC);
			return (FAILURE);
		}
		cmds_head = cmds_head->next;
		i++;
	}
	return (SUCCESS);
}

int launch_prog(t_list *cmd, t_exec_info *info)
{
	char	*path;
	char	**argv;
	char	**env;

	path = get_path((char *)cmd->content, info->env);
	if (!path)
	{
		//il faut utiliser fprintf(stderr, ...) ici
		fprintln_str(STDERR_FILENO, ERR_COMM_NOT_FOUND);
		return (FAILURE);
	}
	argv = t_list_to_char(cmd);
	if (!argv)
	{
		fprintln_str(STDERR_FILENO, ERR_MEM);
		free(path);
		return (FAILURE);
	}
	env = t_list_to_char(info->env);
	if (!env)
	{
		fprintln_str(STDERR_FILENO, ERR_MEM);
		free(path);
		free_token_list(argv);
		return (FAILURE);
	}
	if (execve(path, argv, env))
	{
		free(path);
		free_token_list(argv);
		free_token_list(env);
		return (FAILURE);
	}
}
