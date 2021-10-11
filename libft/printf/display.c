/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:34:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:27:44 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	display_nbrs(char **format, va_list ap, t_flags *flags, int fd)
{
	char	*s;
	char	*tmp;
	ssize_t	len;

	if (**format == 'd' || **format == 'i')
		s = format_ints(ft_itoa(va_arg(ap, int)), flags);
	else if (**format == 'u')
		s = format_ints(ft_ulltoa(va_arg(ap, unsigned int)), flags);
	else if (**format == 'x')
		s = format_ints(ft_ulltohex(va_arg(ap, unsigned int)), flags);
	else if (**format == 'p')
	{
		tmp = ft_ulltohex((uintptr_t)va_arg(ap, void *));
		s = format_ints(ft_strjoin("0x", tmp), flags);
		free(tmp);
	}
	else
		s = format_ints(ft_ulltoupperhex(va_arg(ap, unsigned int)), flags);
	(*format)++;
	if (!s)
		return (0);
	len = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}

int	display_char(char **format, va_list ap, t_flags *flags, int fd)
{
	char	*s;
	char	*tmp;
	size_t	len;

	(*format)++;
	tmp = malloc(sizeof(char) * 1);
	if (!tmp)
		return (0);
	*tmp = va_arg(ap, int);
	if (flags->length > 0)
		flags->length -= 1;
	s = format_strings(ft_strdup(""), flags);
	len = 1;
	if (flags->left_justify)
		write(fd, tmp, 1);
	len += write(fd, s, ft_strlen(s));
	if (!flags->left_justify)
		write(fd, tmp, 1);
	free(tmp);
	free(s);
	return (len);
}

int	display_strings(char **format, va_list ap, t_flags *flags, int fd)
{
	char	*s;
	size_t	len;

	if (**format == 's')
	{
		s = va_arg(ap, char *);
		if (s)
			s = ft_strdup(s);
	}
	else
		s = format_percent(flags);
	s = format_strings(s, flags);
	if (s == NULL)
		return (0);
	(*format)++;
	len = write(fd, s, ft_strlen(s));
	free(s);
	return (len);
}
