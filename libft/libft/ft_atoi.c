/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:40:56 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/28 16:16:45 by lgaudet-         ###   ########lyon.fr   */
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

int	result(int neg, long long res)
{
	res *= neg;
	if (res > INT_MAX)
		res = INT_MAX;
	else if (res < INT_MIN)
		res = INT_MIN;
	return (res);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	const char	*s;
	int			neg;
	long long	res;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	neg = 1;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	res = 0;
	s = str + i;
	i = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	return (result(neg, res));
}
