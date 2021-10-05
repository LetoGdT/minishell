/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/05 16:29:21 by mballet          ###   ########.fr       */
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
# include "../libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# define FAILURE 0
# define SUCCESS 1

typedef enum e_states
{
	_START,
	_DEFAULT,
	_REDIR_SINGLE,
	_REDIR_DOUBLE,
	_QUOTES
}	t_states;

typedef struct s_cmd
{
	t_list	*cmd;
	t_list	*s_red_in;
	t_list	*s_red_out;
	t_list	*d_red_in;
	t_list	*d_red_out;
}	t_cmd;

typedef struct s_exec_info
{
	t_list	*cmds;
	pid_t	*pids;
	t_list	*env;
}	t_exec_info;

typedef struct s_builtin
{
	char	*name;
	int		default_fork;
	int		(*fun)(int argc, char **argv, t_list **env);
}	t_builtin;

//Fonctions liées à l’environnement
char	**ft_getenv(t_list *env);
t_list	*ft_new_env(char *env[]);
int 	try_add(const char *str, t_list **env);
int		ft_remove_from_env(char *key, t_list **env);
char	**ft_getenv_entry(char *key, t_list *env);
char	*ft_getenv_value(char *key, t_list *env);

// #Fonctions liées à l’éxecution
int			exec(int *stat_loc, t_exec_info *info);
char		*get_path(char *cmd, t_list *env);

// #Fonctions sur les signaux
void		sig_handler(int signo);
void		sig_int(t_exec_info info);
void		sig_quit(t_exec_info info);

// #Fonctions pour le parsing
short int	parsing(char **line, t_exec_info **global);
short int	var_env(char **line, t_exec_info *global);
short int	error_multi_line(char *line);
short int	tokenizing(t_exec_info **global, char *line);
int short	state_default(t_cmd *cmds, char *line, int *i);
short int	trim_space(char **line);

	// #Fontions utils du parsing
short int	is_brackets_quote(char c);
short int	is_separator(char c);
short int	is_quotes_pipe(char c);
short int	is_pipe(char c);
// void		print_cmd(t_cmd *cmds);
void		print_cmds_cmd(t_cmd *content);
short int	is_state_symbol(char c);

// #Fonctions pour init
short int	init(t_exec_info **global, char **env);
// short int	init_cmds(t_exec_info *global);
short int	init_cmds(t_list **cmds);

// #Fonctions pour free avant d'exit
short int	clear(t_exec_info **global, char **line, int ret);
void		clear_cmds(t_list *cmds);

//Builtins
int		ft_export(int argc, char **argv, t_list **env);
int		ft_unset(int argc, char **argv, t_list **env);
int		ft_env(int argc, char **argv, t_list **env);

#endif
