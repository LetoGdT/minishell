/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:02:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:35:28 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	display_format(char **format, va_list ap, t_flags *flags, int fd)
{
	if (**format == 'd' || **format == 'i' || **format == 'u' || \
		**format == 'x' || **format == 'X' || **format == 'p')
		return (display_nbrs(format, ap, flags, fd));
	if (**format == 'c')
		return (display_char(format, ap, flags, fd));
	if (**format == 's' || **format == '%')
		return (display_strings(format, ap, flags, fd));
	return (0);
}
