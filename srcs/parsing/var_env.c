/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/10/06 11:03:23 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	get_new_line(char **line, char *key, char *value, int loc)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strdup(*line);
	if (!str)
		return (FAILURE);
	*line = ft_realloc(*line, (ft_strlen(*line) - ft_strlen(key) \
		+ ft_strlen(value) + 1));
	if (!(*line))
		return (FAILURE);
	j = loc + 1;
	i = -1;
	while (value[i + 1])
	{
		(*line)[++loc] = value[++i];
	}
	j += ft_strlen(key);
	while (str[j])
	{
		(*line)[++loc] = str[++j];
	}
	(*line)[++loc] = 0;
	free(str);
	return (SUCCESS);
}

static char	*get_key(char *line, int loc)
{
	int		i;
	char	*str;

	i = 0;
	while (line[loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc]))
	{
		loc++;
		i++;
	}
	loc -= i;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc]))
	{
		str[i] = line[loc];
		loc++;
		i++;
	}
	str[i] = 0;
	return (str);
}

static short int	trim_dollar(t_exec_info *global, char **line, int loc)
{
	char	*key;
	char	*value;

	key = get_key(*line, loc + 1);
	if (!key)
		return (FAILURE);
	value = ft_getenv_value(key, global->env);
	if (!value)
		return (FAILURE);
	if (!get_new_line(line, key, value, loc - 1))
		return (FAILURE);
	free(value);
	free(key);
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

short int	var_env(char **line, t_exec_info *global)
{
	int			i;
	short int	ret;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != ' ' \
			&& !in_s_quote(*line, i))
		{
			ret = trim_dollar(global, line, i);
			if (!ret)
				return (FAILURE);
			i = 0;
		}
		i++;
	}
	return (SUCCESS);
}