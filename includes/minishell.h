/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/13 18:30:14 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_env
{
}	t_env;

typef enum e_op
{
	_OP_AND,
	_OP_OR,
	_OP_PIPE
}	t_op;

typef enum e_redir
{
	_REDIR_SINGLE,
	_REDIR_DOUBLE
}	t_redir;

typedef struct s_exec_info
{
	char	**commands;
	t_op	*ops;
	char	*infile;
	char	*outfile;
	int		in_redir;
	int		out_redir;
	pid_t	*pids;
	t_env	env;
}	t_exec_info;

#Fonctions liées à l’environnement
char	**ft_getenv(t_env *env);
t_env	*ft_new_env(char *env[]);
int		ft_add_to_env(char *key, char *val, t_env *env);
int		ft_remove_from_env(char *key, t_env *env);
char	*ft_getenv_value(char *key, t_env *env);

#Fonctions liées à l’éxecution
int		exec(int *stat_loc, t_exec_info info);
char	*get_path(char *cmd, t_env *env);

#Fonctions sur les signaux
void	sig_handler(int signo);
void	sig_int(t_info);
void	sig_quit(t_info);

#endif
