/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:57:00 by mballet           #+#    #+#             */
/*   Updated: 2021/09/23 16:32:08 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_nbr {
	int	nb;
	int	localisation;
}	t_nbr;

static short int	char_even(char *str, char c)
{
	int	i;
	int	nbr_c;

	i = 0;
	nbr_c = 0;
	while (str[i])
	{
		if (str[i] == c)
			nbr_c++;
		i++;
	}
	if (nbr_c % 2)
		return (FAILURE);
	return (SUCCESS);
}

static short int	special_char_match(char *str, char c, char match)
{
	int		i;
	t_nbr	t_c;
	t_nbr	t_match;

	i = ft_strlen(str);
	t_c.nb = 0;
	t_c.localisation = 0;
	t_match.nb = 0;
	t_match.localisation = 0;
	while (--i)
	{
		if (str[i] == c)
		{
			t_c.nb++;
			t_c.localisation = i;
		}
		if (str[i] == match)
		{
			t_match.nb++;
			t_match.localisation = i;
		}
	}
	if (t_c.nb != t_match.nb || t_c.localisation > t_match.localisation)
		return (FAILURE);
	return (SUCCESS);
}

static short int	error_multi_line(char *line)
{
	if (!char_even(line, '\'') \
		|| !char_even(line, '\"'))
	{
		return (FAILURE);
	}
	if (!special_char_match(line, '(', ')') \
		|| !special_char_match(line, '[', ']') \
		|| !special_char_match(line, '{', '}'))
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

int short	basic_errors(char *line)
{
	if (!error_multi_line(line))
	{
		return (FAILURE);
	}
	return (SUCCESS);
}