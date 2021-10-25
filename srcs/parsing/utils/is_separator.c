/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:42:29 by mballet           #+#    #+#             */
/*   Updated: 2021/10/25 16:25:04 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int short	is_separator(char c)
{
	if (is_quotes_pipe(c) || c == '<' || c == '>' || c == ' ')
		return (SUCCESS);
	return (FAILURE);
}
