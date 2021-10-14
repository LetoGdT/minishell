/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:07:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/13 13:21:58 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	if (!str || !f)
		return (NULL);
	ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	i = -1;
	while (ret[++i])
		ret[i] = (*f)(i, ret[i]);
	return (ret);
}
