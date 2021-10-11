/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:47:10 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/11 19:50:09 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <libft.h>
#include <wchar.h>

typedef struct s_flags
{
	int			left_justify;
	int			zero;
	int			precision;
	int			length;
}				t_flags;
int				display_format(char **format, va_list ap, t_flags *flags, \
				int fd);
void			detecte_flags(char **format, va_list ap, t_flags *flags);
char			*ft_ulltoa(unsigned long long n);
char			*ft_ulltohex(unsigned long long n);
char			*ft_ulltoupperhex(unsigned long long n);
int				max_int(int a, int b);
int				display_nbrs(char **format, va_list ap, t_flags *flags, int fd);
char			*format_ints(char *source, t_flags *flags);
char			*format_strings(char *source, t_flags *flags);
char			*format_percent(t_flags *flags);
int				ft_abs(int n);
int				display_char(char **format, va_list ap, t_flags *flags, int fd);
int				display_strings(char **format, va_list ap, t_flags *flags, \
				int fd);
char			*free_and_ret_null(char *str);
#endif
