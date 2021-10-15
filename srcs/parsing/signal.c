/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:43:15 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/15 14:52:56 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_quit(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		write(1, "\b\\Quit: 3\n", 10);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_int(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		// ft_fprintf(STDOUT_FILENO, "\n");
		rl_on_new_line();
		rl_replace_line("\n", 0);
		rl_redisplay();
	}
}
