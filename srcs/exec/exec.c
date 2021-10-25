/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/25 17:47:15 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec(t_exec_info info)
{
	t_list		*head;
	t_run_info	run;
	pid_t		last_pid;
	int			rank;

	if (info.cmds == NULL)
		return (SUCCESS);
	if (!init_exec(&run, info))
		return (FAILURE);
	head = info.cmds;
	rank = 0;
	while (head)
	{
		last_pid = launch_cmd(rank, head, &run, info);
		if (last_pid == -1)
			return (SUCCESS);
		if (last_pid == -2)
			return (FAILURE);
		head = head->next;
		rank++;
	}
	return (wait_children_and_set_exit_code(last_pid, &info.env));
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

pid_t	prepare_fork_pipe(int rank, t_list *head, t_run_info *run)
{
	if (head->next != NULL)
	{
		if (pipe(run->right_pipe))
			return (-1);
	}
	else
		run->right_pipe[1] = -1;
	if (((t_cmd *)head->content)->args != NULL && head->next == NULL && \
		rank == 0 && !builtin_get_default_fork((char *) \
		((t_cmd *)head->content)->args->content))
		return (-2);
	g_children_running = 1;
	return (fork());
}
