/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/14 19:07:48 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec(t_exec_info info)
{
	t_list		*head;
	t_run_info	run;
	pid_t		pid;
	int			i;
	int			res;

	if (!init_exec(&run))
		return (FAILURE);
	head = info.cmds;
	i = 0;
	while (head)
	{
		pid = prepare_fork_pipe(i, head, &run);
		if (pid == -2)
		{
			child((t_cmd *)head->content, &run, info);
			return (SUCCESS);
		}
		else if (pid == 0)
		{
			child((t_cmd *)head->content, &run, info);
			res = ft_atoi(ft_getenv_value("?", info.env));
			exit(res);
		}
		else if (pid > 0)
			parent(i, &run);
		else
		{
			perror(ERR_EXEC);
			clear(info, NULL, 0);
			return (FAILURE);
		}
		head = head->next;
		i++;
	}
	wait_children(pid, &i);
	if (WIFEXITED(i))
		return (change_env_dollar_question(WEXITSTATUS(i), &info.env));
	if (WIFSIGNALED(i))
		return (change_env_dollar_question(WTERMSIG(i) + 128, &info.env));
	return (FAILURE);
}

int	child(t_cmd *cmd, t_run_info *run, t_exec_info info)
{
	if (!prepare_redir(cmd, run))
	{
		perror(ERR_REDIR);
		return (FAILURE);
	}
	if (!launch_prog(cmd, info))
		return (FAILURE);
	if (!restore_io(run))
	{
		perror(ERR_REDIR);
		return (FAILURE);
	}
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

int	launch_prog(t_cmd *cmd, t_exec_info info)
{
	char		**argv;
	int			res;
	t_built_fun	fun;

	argv = t_list_to_char(cmd->args);
	if (!argv)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_MEM);
		return (FAILURE);
	}
	fun = builtin_get_fun_ptr((char *)cmd->args->content);
	if (fun)
	{
		res = (fun)(ft_lstsize(cmd->args), argv, &info.env);
		ft_free_token_list(argv);
		return (change_env_dollar_question(res, &info.env));
	}
	return (!call_execve(argv, cmd, info));
}

int	call_execve(char **argv, t_cmd *cmd, t_exec_info info)
{
	char	*path;
	char	**env;

	path = get_path((char *)cmd->args->content, info.env);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_COMM_NOT_FOUND);
		ft_free_token_list(argv);
		return (FAILURE);
	}
	env = t_list_to_char(info.env);
	if (!env)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_MEM);
		free(path);
		ft_free_token_list(argv);
		return (FAILURE);
	}
	clear(info, NULL, 0);
	if (execve(path, argv, env))
	{
		free(path);
		ft_free_token_list(argv);
		ft_free_token_list(env);
	}
	perror(MINISHELL);
	return (FAILURE);
}
