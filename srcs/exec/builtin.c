/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:13:25 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/05 19:55:51 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define NB_BUILTIN 5

static t_builtin *get_fun_list(void)
{
	static const t_builtin	fun_list[NB_BUILTIN] = {
	{"cd", 0, ft_cd},
	{"pwd", 1, ft_pwd},
	{"export", 0, ft_export},
	{"unset", 0, ft_unset},
	{"env", 1, ft_env}};

	return ((t_builtin *)fun_list);
}

int builtin_get_default_fork(char *cmd_name)
{
	t_builtin	*fun_list;
	int			i;

	fun_list = get_fun_list();
	i = 0;
	while (i < NB_BUILTIN)
	{
		if (!ft_strncmp(cmd_name, fun_list[i].name, ft_strlen(fun_list[i].name)))
			return (fun_list[i].default_fork);
		i++;
	}
	return (SUCCESS);
}

t_built_fun	builtin_get_fun_ptr(char *cmd_name)
{
	t_builtin	*fun_list;
	int			i;

	fun_list = get_fun_list();
	i = 0;
	while (i < NB_BUILTIN)
	{
		if (!ft_strncmp(cmd_name, fun_list[i].name, ft_strlen(fun_list[i].name)))
			return (fun_list[i].fun);
		i++;
	}
	return (NULL);
}
