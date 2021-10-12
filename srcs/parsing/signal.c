/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:43:15 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 18:25:25 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		sig_quit(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void		sig_int(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		ft_fprintf(STDOUT_FILENO, "\n");
		//rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
	}
}
