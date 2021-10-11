/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:50:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:51:48 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char	*apply_precision_zero(char *source, t_flags *flags)
{
	size_t	len;
	size_t	i;
	char	*tmp;
	int		neg;

	tmp = ft_strdup(source);
	neg = *source == '-';
	if (flags->precision != -1 || flags->zero)
	{
		len = max_int(max_int(ft_strlen(source + neg), \
		flags->precision), flags->zero - neg);
		free(source);
		source = malloc(sizeof(char) * (len + 1 + neg));
		if (!source)
			return (free_and_ret_null(tmp));
		source[0] = '-';
		i = 0;
		while (i < len - ft_strlen(tmp + neg))
			source[i++ + neg] = '0';
		ft_strlcpy(source + i + neg, tmp + neg, ft_strlen(tmp + neg) + 1);
	}
	free(tmp);
	return (source);
}

static char	*apply_spaces(char *source, t_flags *flags)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	len = ft_strlen(source);
	if ((size_t)flags->length <= len)
		return (source);
	tmp = ft_strdup(source);
	free(source);
	source = malloc(sizeof(char) * (flags->length + 1));
	if (!source)
		return (free_and_ret_null(tmp));
	i = 0;
	while (i < (size_t)flags->length)
		source[i++] = ' ';
	if (flags->left_justify)
		i = 0;
	else
		i = (size_t)flags->length - len;
	ft_memcpy(source + i, tmp, len);
	source[flags->length] = '\0';
	free(tmp);
	return (source);
}

char	*format_ints(char *source, t_flags *flags)
{
	if (flags->zero && flags->precision != -1)
	{
		flags->length = max_int(flags->length, flags->zero);
		flags->zero = 0;
	}
	if (flags->precision == 0 && source[0] == '0' && source[1] == '\0')
	{
		free(source);
		source = ft_strdup("");
	}
	else if (flags->precision == 0 && !ft_strncmp("0x0", source, 4))
	{
		free(source);
		source = ft_strdup("0x");
	}
	else
	{
		source = apply_precision_zero(source, flags);
		if (!source)
			return (NULL);
	}
	source = apply_spaces(source, flags);
	if (!source)
		return (NULL);
	return (source);
}

char	*format_strings(char *source, t_flags *flags)
{
	char	*dest;
	size_t	len;
	size_t	i;

	if (source == NULL)
		source = ft_strdup("(null)");
	if ((size_t)flags->precision < ft_strlen(source) && flags->precision != -1)
		source[flags->precision] = '\0';
	len = max_int(flags->length, ft_strlen(source));
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (free_and_ret_null(source));
	i = 0;
	while (i < len)
		dest[i++] = ' ';
	if (flags->left_justify)
		i = 0;
	else
		i = len - ft_strlen(source);
	ft_memcpy(dest + i, source, ft_strlen(source));
	dest[len] = '\0';
	free(source);
	return (dest);
}

char	*format_percent(t_flags *flags)
{
	char	*dest;
	size_t	len;
	size_t	i;

	if (flags->zero < 2)
		len = 1;
	else
		len = flags->zero;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len - 1)
		dest[i++] = '0';
	dest[i++] = '%';
	dest[i] = '\0';
	flags->precision = 1;
	return (dest);
}
