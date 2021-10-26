/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_leftover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:29:12 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 12:41:30 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_leftover(char **line, char *str, int loc, int j)
{
	while (str[j])
		(*line)[++loc] = str[++j];
	(*line)[++loc] = 0;
}