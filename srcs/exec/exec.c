/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/05 21:30:21 by lgaudet-         ###   ########.fr       */
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
	head = info->cmds;
	i = 0;
	while (head)
	{
		pid = prepare_fork_pipe(i, head, &run);
		if (pid == -2)
		{
			child(pid, (t_cmd *)head->content, &run, info);
			return (SUCCESS);
		}
		else if (pid == 0)
		{
			child(pid, (t_cmd *)head->content, &run, info);
			exit(ft_atoi(ft_getenv_value("?", info->env)));
		}
		else if (pid > 0)
			parent(i, &run);
		else
		{
			perror(ERR_EXEC);
			return (FAILURE);
		}
		head = head->next;
		i++;
	}
	wait_children(pid, &i, i);
	if (WIFEXITED(i))
		return (change_env_dollar_question(WEXITSTATUS(i), &info->env));
	return (SUCCESS);
}

int	child(pid_t pid, t_cmd *cmd, t_run_info *run, t_exec_info *info)
{
	if (!prepare_redir(cmd, run))
		return (FAILURE);
	if (!launch_prog(pid, cmd, info))
		return (FAILURE);
	if (!restore_io(run))
		return (FAILURE);
	return (SUCCESS);
}

int	parent(int rank, t_run_info *run)
{
	if (rank != 0)
	{
		close(run->left_pipe[0]);
		close(run->left_pipe[1]);
	}
	run->left_pipe[0] = run->right_pipe[0];
	run->left_pipe[1] = run->right_pipe[1];
	return (SUCCESS);
}

int	launch_prog(pid_t pid, t_cmd *cmd, t_exec_info *info)
{
	char		**argv;
	int			res;
	t_built_fun	fun;

	argv = t_list_to_char(cmd->cmd);
	if (!argv)
	{
		fprintln_str(STDERR_FILENO, ERR_MEM);
		return (FAILURE);
	}
	fun = builtin_get_fun_ptr((char *)cmd->cmd->content);
	if (fun)
	{
		res = (fun)(ft_lstsize(cmd->cmd), argv, &info->env);
		free_token_list(argv);
		if (pid != 0)
			return (change_env_dollar_question(res, &info->env));
		return (SUCCESS);
	}
	return (!call_execve(argv, cmd, info));
}

int	call_execve(char **argv, t_cmd *cmd, t_exec_info *info)
{
	char	*path;
	char	**env;

	path = get_path((char *)cmd->cmd->content, info->env);
	if (!path)
	{
		//il faut utiliser fprintf(stderr, ...) ici
		fprintln_str(STDERR_FILENO, ERR_COMM_NOT_FOUND);
		free_token_list(argv);
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
	}
		// faire l’affichage d’erreur
	return (FAILURE);
}
