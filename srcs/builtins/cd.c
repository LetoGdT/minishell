/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 22:18:37 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/27 15:56:01 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int change_pwd(char *target_dir, t_list **env)
{
	char	*tmp;
	int		res;

	tmp = ft_strjoin(PWD, target_dir);
	if (!tmp)
		return (FAILURE);
	res = try_add(tmp, env);
	free(tmp);
	return (res);
}

int	ft_cd(int argc, char **argv, t_list **env)
{
	char	*target_dir;
	int		res;

	if (argc == 1)
	{
		target_dir = ft_getenv_value(HOME, *env);
		if (!target_dir)
		{
			fprint_str(STDERR_FILENO, ERR_MSG_CD_HOME);
			return (FAILURE);
		}
	}
	else
		target_dir = ft_strdup(argv[1]);
	if (chdir(target_dir))
	{
		perror(ERR_MSG_CD);
		free(target_dir);
		return (FAILURE);
	}
	res = change_pwd(target_dir, env);
	free(target_dir);
	return (res);
}

int	ft_pwd(int argc, char **argv, t_list **env)
{
	char	*dir_path;

	(void)argc;
	(void)argv;
	(void)env;
	dir_path = getcwd(NULL, 0);
	if (!dir_path)
	{
		perror(NULL);
		return (FAILURE);
	}
	printf("%s\n", dir_path);
	free(dir_path);
	return (SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	t_list *t_env = ft_new_env(env);
	ft_cd(argc, argv, &t_env);
	ft_env(argc, argv, &t_env);
	return (0);
}
