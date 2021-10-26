/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:27:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 16:16:54 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strdup_double(char **str)
{
	char	**new;
	size_t	size;
	size_t	size_bis;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	size = 0;
	while (str[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		size_bis = 0;
		j = 0;
		while (str[i][j])
		{
			j++;
			size_bis++;
		}
		new[i] = malloc(sizeof(char) * size_bis + 1);
		if (!new[i])
			return (FAILURE);
		j = 0;
		while (str[i][j])
		{
			new[i][j] = str[i][j];
			j++;
		}
		new[i][j] = 0;
		i++;
	}
	new[i] = 0;
	return (new);
}
