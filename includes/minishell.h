/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/16 16:43:18 by lgaudet-         ###   ########.fr       */
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
# include "libft.h"
# define SUCESS 1
# define FAILURE 0

typef enum e_redir
{
	_REDIR_SINGLE,
	_REDIR_DOUBLE
}	t_redir;

typedef struct s_exec_info
{
	char	**commands;
	char	*infile;
	char	*outfile;
	int		in_redir;
	int		out_redir;
	pid_t	*pids;
	t_list	*env;
}	t_exec_info;

#Fonctions liées à l’environnement
char	**ft_getenv(t_env *env);
t_list	*ft_new_env(char *env[]);
int		ft_add_to_env(char *val, t_list **env);
int		ft_remove_from_env(char *key, t_list **env);
char	*ft_getenv_value(char *key, t_list *env);

#Fonctions liées à l’éxecution
int		exec(int *stat_loc, t_exec_info *info);
char	*get_path(char *cmd, t_env *env);

#Fonctions sur les signaux
void	sig_handler(int signo);
void	sig_int(t_info);
void	sig_quit(t_info);

#endif
