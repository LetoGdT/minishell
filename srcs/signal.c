/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:43:15 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/08 20:09:46 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		sig_handler(int signo);
void		sig_int(int signo)
{
	(void)signo;
	if (g_children_running)
	{
		signal(SIGINT, SIG_IGN);
		kill(0, SIGINT);
		signal(SIGINT, sig_int);
	}
	//revenir au readline dans le main
}

void		sig_quit(int signo)
{
	(void)signo;
	kill(0, SIGQUIT);
}
