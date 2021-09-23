/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 21:25:53 by lgaudet-         ###   ########.fr       */
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

typedef enum e_redir
{
	_REDIR_SINGLE,
	_REDIR_DOUBLE
}	t_redir;

typedef struct s_cmd
{
	char	*cmd;
	char	*infile;
	char	*outfile;
	t_redir	in_redir;
	t_redir	out_redir;
}	t_cmd;

typedef struct s_exec_info
{
	t_list	*cmds;
	pid_t	*pids;
	t_list	*env;
}	t_exec_info;

//Fonctions liées à l’environnement
char	**ft_getenv(t_list *env);
t_list	*ft_new_env(char *env[]);
int		ft_add_to_env(char *val, t_list **env);
int		ft_remove_from_env(char *key, t_list **env);
char	*ft_getenv_value(char *key, t_list *env);

//Fonctions liées à l’éxecution
int		exec(int *stat_loc, t_exec_info *info);
char	*get_path(char *cmd, t_list *env);

//Fonctions sur les signaux
void	sig_handler(int signo);
void	sig_int(t_exec_info info);
void	sig_quit(t_exec_info info);

//Builtins
int		echo(int argc, char **argv, t_list **env);


#endif
