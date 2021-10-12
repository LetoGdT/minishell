/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/12 22:15:34 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/includes/libft.h"
# include "const.h"
# include "error.h"

extern int	g_children_running;

typedef enum e_states
{
	_START,
	_DEFAULT,
	_RED_SINGLE,
	_RED_DOUBLE,
	_QUOTES
}	t_states;

typedef enum e_redir
{
	_REDIR_SINGLE,
	_REDIR_DOUBLE
}	t_redir;

typedef struct s_file_redir
{
	char	*name;
	t_redir	count;
}	t_file_redir;

typedef struct s_cmd
{
	t_list	*args;
	t_list	*infile;
	t_list	*outfile;
}	t_cmd;

typedef struct s_exec_info
{
	t_list	*cmds;
	pid_t	*pids;
	t_list	*env;
}	t_exec_info;

typedef int	(*t_built_fun)(int, char **, t_list **);
typedef struct s_builtin
{
	char	*name;
	int		default_fork;
	int		(*fun)(int argc, char **argv, t_list **env);
}	t_builtin;

typedef struct s_run_info
{
	int		fd_real_in;
	int		fd_real_out;
	int		left_pipe[2];
	int		right_pipe[2];
}	t_run_info;

//Fonctions liées à l’environnement
char		**ft_getenv(t_list *env);
t_list		*ft_new_env(char *env[]);
int			try_add(const char *str, t_list **env);
int			ft_remove_from_env(char *key, t_list **env);
char		**ft_getenv_entry(char *key, t_list *env);
char		*ft_getenv_value(char *key, t_list *env);
int			change_env_dollar_question(int n, t_list **env);
char		**t_list_to_char(t_list *lst);

// Fonctions liées à l’éxecution
int			init_exec(t_run_info *run);
int			exec(t_exec_info info);
pid_t		prepare_fork_pipe(int rank, t_list *head, t_run_info *run);
int			launch_prog(pid_t pid, t_cmd *cmd, t_exec_info info);
int			call_execve(char **argv, t_cmd *cmd, t_exec_info info);
int			child(pid_t pid, t_cmd *cmd, t_run_info *run, t_exec_info info);
void		wait_children(pid_t last_child, int *stat_loc);
int			parent(int rank, t_run_info *run);
int			prepare_redir(t_cmd *cmd, t_run_info *run);
int			restore_io(t_run_info *run);
int			builtin_get_default_fork(char *cmd_name);
t_built_fun	builtin_get_fun_ptr(char *cmd_name);
char		*get_path(char *cmd, t_list *env);

// Fonctions sur les signaux
void		sig_handler(int signo);
void		sig_int(int signo);
void		sig_quit(int signo);

// #Fonctions pour le parsing
short int	parsing(char **line, t_exec_info *global);
short int	var_env(char **line, t_exec_info *global);
short int	error_multi_line(char *line);
short int	tokenizing(t_exec_info *global, char *line);
int short	state_default(t_cmd *cmds, char *line, int *i);
int short	state_redir(t_cmd *cmds, char *line, int *i, t_states *st);
int short	state_quotes(t_cmd *content, char *line, int *i, char c);
short int	trim_space(char **line);

// Fontions utils du parsing
short int	is_brackets_quote(char c);
short int	is_separator(char c);
short int	is_quotes_pipe(char c);
short int	is_pipe(char c);
void		print_cmds(t_exec_info global);
void		print_content_args(t_cmd *content);
void		print_content_infile(t_cmd *content);
void		print_content_outfile(t_cmd *content);
short int	is_state_symbol(char c);
short int	is_space_and_next(char *str, int i, char c);

// #Fonctions pour init
short int	init(t_exec_info *global, char **env);
t_list		*init_content(void);

// #Fonctions pour free avant d'exit
short int	clear(t_exec_info global, char *line, int ret);
void		clear_cmds(t_exec_info global);
void		ft_lstclear_redir(t_list **lst, void (*del)(void*), \
				short int nb);
void		del(void *content);

//Builtins
int			ft_export(int argc, char **argv, t_list **env);
int			ft_unset(int argc, char **argv, t_list **env);
int			ft_env(int argc, char **argv, t_list **env);
int			ft_cd(int argc, char **argv, t_list **env);
int			ft_pwd(int argc, char **argv, t_list **env);
int			ft_exit(int argc, char **argv, t_list **env);
int			ft_echo(int argc, char **argv, t_list **env);

#endif
