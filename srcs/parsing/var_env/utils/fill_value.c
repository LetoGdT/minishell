/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:28:56 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 12:45:53 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	fill_value(char *value, char **line, int *loc, char ***esc_quote)
{
	int	i;

	i = -1;
	while (value[i + 1])
	{
		if (value[i + 1] == '\'' || value[i + 1] == '\"')
			if (!fill_esc_quote(esc_quote, *loc + 1))
				return (FAILURE);
		(*line)[++(*loc)] = value[++i];
	}
	return (SUCCESS);
}