/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:30:07 by mballet           #+#    #+#             */
/*   Updated: 2021/10/20 17:00:20 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_or_double(t_file_redir **redir, t_states *st, int *i)
{
	if (*st == _RED_SINGLE)
		(*redir)->count = _REDIR_SINGLE;
	else if (*st == _RED_DOUBLE)
	{
		(*redir)->count = _REDIR_DOUBLE;
		(*i)++;
	}
}

static int	find_size(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{
		size++;
		i++;
	}
	return (size);
}

static int short	infile(t_file_redir *redir, t_cmd *content, \
						char *line, int *i)
{
	t_list	*new;
	int		size;

	(*i)++;
	if (line[*i] == ' ')
		(*i)++;
	size = find_size(line, *i, ' ');
	if (!size)
		return (ERR_PARSING);
	redir->name = malloc(sizeof(char) * (size + 1));
	if (!redir->name)
		return (FAILURE);
	size = 0;
	while (line[(*i)] && line[(*i)] != ' ')
	{
		(redir->name)[size] = line[*i];
		(*i)++;
		size++;
	}
	(redir->name)[size] = 0;
	new = ft_lstnew(redir);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(&(content->infile), new);
	return (SUCCESS);
}

static int short	outfile(t_file_redir *redir, t_cmd *content, \
						char *line, int *i)
{
	t_list	*new;
	int		size;

	(*i)++;
	if (line[*i] == ' ')
		(*i)++;
	size = find_size(line, *i, ' ');
	if (!size)
		return (ERR_PARSING);
	redir->name = malloc(sizeof(char) * (size + 1));
	if (!redir->name)
		return (FAILURE);
	size = 0;
	while (line[(*i)] && line[(*i)] != ' ')
	{
		(redir->name)[size] = line[*i];
		(*i)++;
		size++;
	}
	(redir->name)[size] = 0;
	new = ft_lstnew(redir);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(&(content->outfile), new);
	return (SUCCESS);
}

int short	state_redir(t_cmd *content, char *line, int *i, t_states *st)
{
	t_file_redir	*redir;
	int				ret;

	ret = SUCCESS;
	redir = malloc(sizeof(t_file_redir));
	if (!redir)
		return (FAILURE);
	simple_or_double(&redir, st, i);
	if (line[*i] == '<')
	{
		ret = infile(redir, content, line, i);
		if (!ret)
			return (FAILURE);
	}
	else if (line[*i] == '>')
	{
		ret = outfile(redir, content, line, i);
		if (!ret)
			return (FAILURE);
	}
	if (ret == ERR_PARSING)
	{
		ft_fprintf(1, "syntax error near unexpected token `newline'\n");
		// write(1, "syntax error near unexpected token `newline'\n", 45);
		free(redir);
	}
	return (ret);
}
