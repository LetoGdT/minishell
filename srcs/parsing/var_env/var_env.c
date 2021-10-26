/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 12:55:43 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *line, int loc, char **esc_quote)
{
	int		i;
	char	*str;

	i = 0;
	while (line[loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc], \
			esc_quote, loc))
	{
		loc++;
		i++;
	}
	loc -= i;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc], \
			esc_quote, loc))
	{
		str[i] = line[loc];
		loc++;
		i++;
	}
	str[i] = 0;
	return (str);
}

// static short int	norm()
// {
	
// }

static short int	trim_dollar(t_exec_info *global, char **line, int loc, \
						char ***esc_quote)
{
	char	*key;
	char	*value;
	char	*str;
	int		j;

	key = get_key(*line, loc + 1, *esc_quote);
	if (!key)
		return (FAILURE);
	value = ft_getenv_value(key, global->env);
	str = ft_strdup(*line);
	if (!str)
		return (FAILURE);
	loc--;
	j = loc + 1;
	if (!value)
	{
		if (!malloc_new_line(line, key, "\0"))
			return (FAILURE);
		if (!fill_value("\0", line, &loc, esc_quote))
			return (FAILURE);
	}
	else
	{
		if (!malloc_new_line(line, key, value))
			return (FAILURE);
		if (!fill_value(value, line, &loc, esc_quote))
			return (FAILURE);
	}
	j += ft_strlen(key);
	fill_leftover(line, str, loc, j);
	if (value)
		free(value);
	free(key);
	free(str);
	return (SUCCESS);
}

static short int	in_s_quote(char *str, int loc)
{
	int	i;
	int	stock_loc_i;

	stock_loc_i = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		else if (str[i] == '\'')
		{
			stock_loc_i = i;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (stock_loc_i && loc < i && loc > stock_loc_i)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

short int	var_env(char **line, t_exec_info *global, char ***esc_quote)
{
	int			i;
	short int	ret;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != ' ' \
			&& !in_s_quote(*line, i))
		{
			ret = trim_dollar(global, line, i, esc_quote);
			if (!ret)
				return (FAILURE);
			i = 0;
		}
		i++;
	}
	return (SUCCESS);
}
