/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:21:15 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/21 21:16:54 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static const char	*set_str_neg(const char *str, int *neg)
{
	const char	*s;

	s = str;
	while (*s && ft_isspace(*s))
		s++;
	*neg = 1;
	if (*s && (*s == '+' || *s == '-'))
		if (*s++ == '-')
			*neg = -1;
	return (s);
}

long long	ft_atoll(const char *str)
{
	const char			*s;
	int					neg;
	unsigned long long	res;
	unsigned long long	cutoff;

	s = set_str_neg(str, &neg);
	cutoff = LLONG_MAX;
	if (neg == -1)
		cutoff = -(unsigned long long)LLONG_MIN;
	res = 0;
	while (*s && *s >= '0' && *s <= '9')
	{
		res *= 10;
		res += *s - '0';
		if (res > cutoff)
		{
			errno = ERANGE;
			return (0);
		}
		s++;
	}
	return (neg * res);
}
