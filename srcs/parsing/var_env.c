/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/09/28 11:04:48 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define NO_KEY 2

static short int	get_new_line(char **line, char *key, char *value, int loc)
{
	char	*str;
	int		i;
	int		j;

	// printf("\033[33mget_new_line\033[0m\n");
	str = ft_strdup(*line);
	if (!str)
		return (FAILURE);
	*line = ft_realloc(*line, (ft_strlen(*line) - ft_strlen(key) \
		+ ft_strlen(value) + 1));
	if (!(*line))
		return (FAILURE);
	j = loc + 1;
	i = 0;
	while (value[i])
	{
		(*line)[loc] = value[i];
		loc++;
		i++;
	}
	j += ft_strlen(key);
	while (str[j])
	{
		(*line)[loc] = str[j];
		j++;
		loc++;
	}
	(*line)[loc] = 0;
	free(str);
	// printf("\033mLINE :%s\n", *line);
	return (SUCCESS);
}

static char	*get_key(char *line, int loc)
{
	int		i;
	char	*str;

	// printf("\033[33mget_key\033[0m\n");
	i = 0;
	while (line[loc] && line[loc] != ' ')
	{
		loc++;
		i++;
	}
	loc -= i;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[loc] && line[loc] != ' ')
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

	// printf("\033[33mtrim_dollar\033[0m\n");
	key = get_key(*line, loc + 1);
	if (!key)
		return (FAILURE);
	// printf("key :%s\n", key);
	value = ft_getenv_value(key, global->env);
	// printf("value :%s\n", value);
	if (!value)
	{
		free(key);
		return (NO_KEY);
	}
	if (!get_new_line(line, key, value, loc))
		return (FAILURE);
	// printf("line at the end :%s\n", *line);
	free(value);
	free(key);
	return (SUCCESS);
}

static short int	in_s_quote(char *str, int loc)
{
	int			i;
	short int	s_quote;

	s_quote = 0;
	i = 0;
	while (i < loc)
	{
		if (str[i] == '\'')
			s_quote++;
		i++;
	}
	if (s_quote % 2)
		return (FAILURE);
	return (SUCCESS);
}

short int	var_env(char **line, t_exec_info *global)
{
	int			i;
	short int	ret;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != ' ' \
			&& in_s_quote(*line, i))
		{
			// printf("line to send to trim_dollar :%s\n", *line);
			ret = trim_dollar(global, line, i);
			if (!ret)
				return (FAILURE);
			if (ret == NO_KEY)
			{
				break;
			}
			i = 0;
		}
		i++;
	}
	return (SUCCESS);
}