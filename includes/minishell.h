/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:32:41 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/23 16:35:43 by mballet          ###   ########.fr       */
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

typedef enum e_redir
{
	_REDIR_SINGLE,
	_REDIR_DOUBLE
}	t_redir;

typedef struct s_cmd
{
	t_list			*cmd;
	t_list			*infile;
	t_list			*outfile;
	t_redir			in_redir;
	t_redir			out_redir;
}	t_cmd;

typedef struct s_exec_info
{
	t_list	*cmds;
	pid_t	*pids;
	t_list	*env;
}	t_exec_info;

// #Fonctions liées à l’environnement
// char	**ft_getenv(t_env *env);
t_list		*ft_new_env(char *env[]);
int			ft_add_to_env(char *val, t_list **env);
int			ft_remove_from_env(char *key, t_list **env);
char		*ft_getenv_value(char *key, t_list *env);

// #Fonctions liées à l’éxecution
int			exec(int *stat_loc, t_exec_info *info);
// char	*get_path(char *cmd, t_env *env);

// #Fonctions sur les signaux
void		sig_handler(int signo);
// void	sig_int(t_info);
// void	sig_quit(t_info);

// #Fonctions pour le parsing
short int	parsing(char *line, t_exec_info **global);
short int	is_special_state(char c);
short int	line_without_dollar(char **line, t_exec_info *global);
int short	basic_errors(char *line);

// #Fonctions pour init
short int	init(t_exec_info **global, char **env);
t_cmd		*init_struct_cmd(void);

// #Fonctions pour free avant d'exit
short int	clear(t_exec_info *global, char **line, int ret);

#endif
