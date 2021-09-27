/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:35:54 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/06/22 19:53:38 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	is_in_string(char c, const char *str)
{
	char	*tmp;

	tmp = (char *)str;
	while (*tmp)
		if (*tmp++ == c)
			return (1);
	return (0);
}
