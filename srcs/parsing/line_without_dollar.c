/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_without_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 11:58:10 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_line(char **line, char *value, int size_key, int i)
{
	char	*str;
	int		j;
	int		k;

	str = malloc(sizeof(char) * ft_strlen(*line) - size_key \
			+ ft_strlen(value) + 1);
	if (!str)
		return (FAILURE);
	j = 0;
	while (j < i)
	{
		str[j] = (*line)[j];
		j++;
	}
	k = 0;
	while (value[k])
		str[j++] = value[k++];
	while ((*line)[i + 3 + size_key])
		str[j++] = (*line)[++i + 3 + size_key];
	str[j] = 0;
	free(*line);
	*line = ft_strdup(str);
	free(str);
	return (SUCCESS);
}

static char	*get_key(char *str, int *size_key)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		i++;
	}
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		key[j] = str[i];
		i++;
		j++;
	}
	key[j] = 0;
	*size_key = j;
	return (key);
}

static int	trim_dollar(char *str, t_exec_info *global, int i, char **line)
{
	char	*key;
	char	*value;
	int		size_key;

	size_key = 0;
	key = get_key(str + i + 1, &size_key);
	if (!key)
		return (FAILURE);
	value = ft_getenv_value(key, global->env);
	if (!value)
	{
		ft_putstr_fd(key, 1);
		write(1, ": command not found me\n", 23);
		free(key);
		return (2);
	}
	free(key);
	if (!get_line(line, value + size_key + 1, size_key, i))
	{
		free(value);
		return (FAILURE);
	}
	free(value);
	return (SUCCESS);
}

short int	line_without_dollar(char **line, t_exec_info *global)
{
	char		*str;
	int			i;
	short int	ret;

	(void)global;
	str = ft_strdup(*line);
	if (!str)
		return (FAILURE);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
		{
			ret = trim_dollar(str, global, i, line);
			if (!ret)
				return (FAILURE);
		}
		i++;
	}
	free(str);
	return (SUCCESS);
}
