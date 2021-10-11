/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:48:24 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:36:22 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*ft_ulltoa(unsigned long long n)
{
	char	ret[21];
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	ret[20] = '\0';
	i = 20;
	while (n != 0)
	{
		ret[--i] = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(ret + i));
}

char	*ft_ulltohex(unsigned long long n)
{
	char	ret[17];
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	ret[16] = '\0';
	i = 16;
	while (n != 0)
	{
		ret[--i] = n % 16;
		if (ret[i] < 10)
			ret[i] += '0';
		else
			ret[i] += 'a' - 10;
		n /= 16;
	}
	return (ft_strdup(ret + i));
}

char	*ft_ulltoupperhex(unsigned long long n)
{
	char	ret[17];
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	ret[16] = '\0';
	i = 16;
	while (n != 0)
	{
		ret[--i] = n % 16;
		if (ret[i] < 10)
			ret[i] += '0';
		else
			ret[i] += 'A' - 10;
		n /= 16;
	}
	return (ft_strdup(ret + i));
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
