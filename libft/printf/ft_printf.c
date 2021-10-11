/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 12:21:39 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:56:19 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	init_flags(t_flags *flags)
{
	flags->left_justify = 0;
	flags->zero = 0;
	flags->precision = -1;
	flags->length = 0;
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int			len;
	va_list		ap;
	char		*f;
	t_flags		flags;

	f = (char *)format;
	len = 0;
	va_start(ap, format);
	while (*f)
	{
		if (*f == '%')
		{
			init_flags(&flags);
			detecte_flags(&f, ap, &flags);
			len += display_format(&f, ap, &flags, fd);
		}
		else
		{
			len++;
			write(fd, f++, 1);
		}
	}
	va_end(ap);
	return (len);
}
