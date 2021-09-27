/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:24:37 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/05/05 16:43:11 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	invert(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
}

static int	malloc_size(int n)
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

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	ret = malloc(sizeof(char) * malloc_size(n));
	if (!ret)
		return (NULL);
	ret[malloc_size(n) - 1] = '\0';
	if (n < 0)
	{
		ret[malloc_size(n) - 2] = '-';
		n *= -1;
	}
	i = 0;
	while (n != 0)
	{
		ret[i++] = n % 10 + '0';
		n /= 10;
	}
	invert(ret);
	return (ret);
}
