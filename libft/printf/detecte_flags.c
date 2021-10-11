/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detecte_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:05:50 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:26:23 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	detecte_len(char **format, va_list ap)
{
	int	res;

	(*format)++;
	res = 0;
	if (**format == '*')
		res = va_arg(ap, int);
	else
	{
		while (**format >= '0' && **format <= '9')
		{
			res = res * 10 + **format - '0';
			(*format)++;
		}
		(*format)--;
	}
	return (res);
}

static void	detecte_zero(char **format, va_list ap, t_flags *flags)
{
	int	tmp;

	tmp = detecte_len(format, ap);
	if (tmp < 0)
	{
		flags->left_justify = 1;
		flags->length = -tmp;
	}
	else
		flags->zero = tmp;
}

static void	detecte_star(va_list ap, t_flags *flags)
{
	int	tmp;

	tmp = va_arg(ap, int);
	flags->length = ft_abs(tmp);
	if (tmp < 0)
		flags->left_justify = 1;
}

static void	detecte_precision(char **format, va_list ap, t_flags *flags)
{
	int	tmp;

	tmp = detecte_len(format, ap);
	if (tmp >= 0)
		flags->precision = tmp;
}

void	detecte_flags(char **format, va_list ap, t_flags *flags)
{
	(*format)++;
	while (**format == '-' || **format == '0' || **format == '*' || \
		**format == '.' || (**format >= '0' && **format <= '9'))
	{
		if (**format == '-')
			flags->left_justify = 1;
		else if (**format == '0')
			detecte_zero(format, ap, flags);
		else if (**format == '*')
			detecte_star(ap, flags);
		else if (**format == '.')
			detecte_precision(format, ap, flags);
		else if (**format >= '0' && **format <= '9')
		{
			(*format)--;
			flags->length = detecte_len(format, ap);
		}
		(*format)++;
	}
	if (flags->left_justify && flags->zero)
	{
		flags->length = flags->zero;
		flags->zero = 0;
	}
}
