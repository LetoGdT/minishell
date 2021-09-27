/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_without_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 14:51:06 by mballet          ###   ########.fr       */
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

	printf("HERE 1\n");
	size_key = 0;
	key = get_key(str + i + 1, &size_key);
	if (!key)
		return (FAILURE);
	printf("HERE 2\n");
	value = ft_getenv_value(key, global->env);
	if (!value)
	{
		ft_putstr_fd(key, 1);
		write(1, ": command not found me\n", 23);
		if (key)
			free(key);
		return (2);
	}
	printf("value :%s\n", value);
	printf("HERE 3\n");
	if (key)
		free(key);
	if (!get_line(line, value + size_key + 1, size_key, i))
	{
		// if (value)
		// 	free(value);
		return (FAILURE);
	}
	// if (value)
	// 	free(value);
	printf("HERE 4\n");
	return (SUCCESS);
}

// static short int	no_s_quote(char *str, int loc)
// {
// 	int			i;
// 	short int	s_quote;

// 	s_quote = 0;
// 	i = 0;
// 	while (i < loc)
// 	{
// 		if (str[i] == '\'')
// 			s_quote++;
// 		i++;
// 	}
// 	if (s_quote % 2)
// 	{
// 		return (FAILURE);
// 	}
// 	return (SUCCESS);
// }

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
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' '/* && no_s_quote(str, i)*/)
		{
			ret = trim_dollar(str, global, i, line);
			if (!ret)
			{
				free(str);
				return (FAILURE);
			}
			printf("line :%s\n", *line);
			if (ret == 2)
				break;
		}
		i++;
	}
	free(str);
	printf("HERE 5\n");
	return (SUCCESS);
}
