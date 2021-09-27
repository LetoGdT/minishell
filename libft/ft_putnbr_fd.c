/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:23:00 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:29:38 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	string_size(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_pow(int base, int exp)
{
	int	res;

	res = base;
	while (--exp)
		res *= base;
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	ret;
	int		i;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		i = string_size(n) - 1;
		while (--i)
		{
			ret = (n / ft_pow(10, i)) % 10 + '0';
			write(fd, &ret, 1);
		}
		ret = n % 10 + '0';
		write(fd, &ret, 1);
	}
}
