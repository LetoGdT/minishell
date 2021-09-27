/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_without_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/09/27 16:00:41 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_key(char *line, int loc)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while (line[loc] != ' ')
// 	{
// 		loc++;
// 		i++;
// 	}
// 	loc -= i;
// 	str = malloc(sizeof(char) * i + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (line[loc] != ' ')
// 	{
// 		str[i] = line[loc];
// 		loc++;
// 		i++;
// 	}
// 	str[i] = 0;
// 	return (str);
// }

static short int	trim_dollar(t_exec_info *global, char **line, int loc)
{
	// char	*key;
	// char	*value;

	// key = get_key(*line, loc + 1);
	// if (!key)
	// 	return (FAILURE);
	// printf("key :%s\n", key);
	// value = ft_getenv_value(key, global->env);
	// printf("value :%s\n", value);
	// if (!value)
	// 	return (FAILURE);
	
	// free(key);
	// free(value);

	(void)global;
	(void)line;
	(void)loc;
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

short int	line_without_dollar(char **line, t_exec_info *global)
{
	int			i;
	char		*str;
	short int	ret;

	str = *line;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ' \
			&& in_s_quote(str, i))
		{
			ret = trim_dollar(global, line, i);
			if (!ret)
				return (FAILURE);
			if (ret == 2)
				break;
			// i = 0;		une fois que j'aurais finis indispensable car sinon si j'ai plusieurs $$, le deuxieme je vais modifier par rapport a l'emplacement du premier
		}
		i++;
	}
	(void)global;
	return (SUCCESS);
}
