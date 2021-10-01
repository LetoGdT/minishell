/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/01 19:54:33 by lgaudet-         ###   ########.fr       */
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
		pid = prepare_fork_pipe(i, cmds_head, &run, info);
		if (pid == -2)
		{
			child((t_cmd *)cmds_head->content, &run, info);
			return (SUCCESS);
		}
		else if (pid == 0)
			exit(child((t_cmd *)cmds_head->content));
		else if (pid > 0)
			parent(i, &run, info);
		else
		{
			perror(ERR_EXEC);
			return (FAILURE);
		}
		cmds_head = cmds_head->next;
		i++;
	}
	waitpid(pid, &i, NULL);
	return (SUCCESS);
}

pid_t	prepare_fork_pipe(int rank, t_list *cmds_head, t_run_info *run, t_exec_info *info)
{
	if (cmds_head->next != NULL)
	{
		if (pipe(run->right_pipe))
			return (-1);
	}
	else
		run->right_pipe[1] = -1;
	if (cmds_head->next == NULL && rank == 0 && \
		!builtin_get_default_fork((char *)cmds_head->content->cmd->content))
		return (-2);
	return (fork());
}

int	child(t_cmd *cmd, t_run_info *run, t_exec_info *info)
{
	if (!prepare_redir(cmd, &run, info))
		return (FAILURE);
	if (!launch_prog(cmd, info))
		return (FAILURE);
	if (!restore_io(&run))
		return (FAILURE);
	//à changer pour mettre la valeur de sortie du builtin
	return (SUCCESS);
}

int	parent(int rank, t_run_info *run, t_exec_info *info)
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

int launch_prog(t_cmd *cmd, t_exec_info *info)
{
	char		**argv;
	int			res;
	builtin_fun	fun;

	argv = t_list_to_char(cmd);
	if (!argv)
	{
		fprintln_str(STDERR_FILENO, ERR_MEM);
		free(path);
		return (FAILURE);
	}
	fun = builtin_get_fun_ptr((char *)cmd->cmd->content);
	if (fun)
	{
		res = (fun)(ft_lstsize(cmd->cmd), argv, &info->env);
		free_token_list(argv);
		return (res);
	}
	//vérifier que la valeur du retour est compatible avec le retour des builtins
	if (!call_execve(argv, cmd, info))
		return (FAILURE);
}

int call_execve(t_list *cmd, t_exec_info *info)
{
	char	*path;
	char	**env;

	path = get_path((char *)cmd->content, info->env);
	if (!path)
	{
		//il faut utiliser fprintf(stderr, ...) ici
		fprintln_str(STDERR_FILENO, ERR_COMM_NOT_FOUND);
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
