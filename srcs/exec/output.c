/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 14:15:34 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:17:24 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fprintln_str(int fd, char *str)
{
	int	i;

	if (!str)
		return (FAILURE);
	i = write (fd, str, ft_strlen(str));
	if (i == -1)
	{
		perror(ERR_ERR);
		return (FAILURE);
	}
	if ((unsigned int)i != ft_strlen(str))
		return (FAILURE);
	i = write (fd, "\n", 1);
	if (i == -1)
	{
		perror(ERR_ERR);
		return (FAILURE);
	}
	if ((unsigned int)i != 1)
		return (FAILURE);
	return (SUCCESS);
}
