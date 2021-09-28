/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_multi_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:57:00 by mballet           #+#    #+#             */
/*   Updated: 2021/09/28 14:09:21 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_special {
	short int	s_quote;
	short int	d_quote;
	short int	r_brackets;			//round
	short int	r_brackets_match;
	short int	c_brackets;			//circle
	short int	c_brackets_match;
	short int	s_brackets;			//square
	short int	s_brackets_match;
}	t_special;

static void	fill_spe(t_special *spe, char c)
{
	if (c == '\'')
		spe->s_quote++;
	if (c == '\"')
		spe->d_quote++;
	if (c == '(')
		spe->r_brackets++;
	if (c == ')')
		spe->r_brackets_match++;
	if (c == '{')
		spe->c_brackets++;
	if (c == '}')
		spe->c_brackets_match++;
	if (c == '[')
		spe->s_brackets++;
	if (c == ']')
		spe->s_brackets_match++;
}

static void	init_spe(t_special *spe)
{
	spe->s_quote = 0;
	spe->d_quote = 0;
	spe->r_brackets = 0;
	spe->r_brackets_match = 0;
	spe->c_brackets = 0;
	spe->c_brackets_match = 0;
	spe->s_brackets = 0;
	spe->s_brackets_match = 0;
}

static short int	check_match(t_special spe)
{
	if (spe.s_quote % 2 || spe.d_quote % 2)
		return (FAILURE);
	if ((spe.r_brackets != spe.r_brackets_match) \
		|| (spe.c_brackets != spe.c_brackets_match) \
		|| (spe.s_brackets != spe.s_brackets_match))
		return (FAILURE);
	return (SUCCESS);
}

short int	error_multi_line(char *line)
{
	int			i;
	t_special	spe;

	init_spe(&spe);
	i = 0;
	while (line[i])
	{
		if (is_brackets_quote(line[i]))
			fill_spe(&spe, line[i]);
		if (line[i] == '\'')
		{
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
				fill_spe(&spe, line[i]);
		}
		else if (line[i] == '\"')
		{
			while (line[i] && line[i] != '\"')
				i++;
			if (line[i] == '\"')
				fill_spe(&spe, line[i]);
		}
		if (spe.s_quote % 2 || spe.d_quote % 2)
			return (FAILURE);
		i++;
	}
	return (check_match(spe));
}
