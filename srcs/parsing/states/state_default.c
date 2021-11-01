// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   state_default.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/04 15:38:16 by mballet           #+#    #+#             */
// /*   Updated: 2021/11/01 11:56:46 by mballet          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static short int	pipe_at_begenning(t_cmd *content, char *line, int *i, int export, char **esc_quote)
// {
// 	t_list	*new;
// 	char	*str;
// 	int		size;

// 	if (!export && is_export_quote(line + *i))
// 		return (export_quote(content, line, i, esc_quote));
// 	size = *i;
// 	while (line[size] && line[size] != ' ')
// 		size++;
// 	if (!(size - *i))
// 		return (SUCCESS);
// 	str = malloc(sizeof(char) * (size - *i + 1));
// 	if (!str)
// 		return (FAILURE);
// 	size = 0;
// 	while (line[size] && line[size] != ' ')
// 	{
// 		str[size] = line[*i];
// 		size++;
// 		(*i)++;
// 	}
// 	str[size] = 0;
// 	new = ft_lstnew(str);
// 	ft_lstadd_back(&(content->args), new);
// 	return (SUCCESS);
// }

// static short int	regular_behavior(t_cmd *content, char *line, int *i, int export, char **esc_quote)
// {
// 	t_list	*new;
// 	char	*str;
// 	int		size;

// 	if (!export && is_export_quote(line + *i))
// 		return (export_quote(content, line, i, esc_quote));
// 	size = *i;
// 	while (line[size] && !is_separator(line[size], esc_quote, size))
// 	{
// 		size++;
// 	}

// //>
// 	if (line[size] && (line[size] == '\'' || line[size] == '\"'))
// 	{
// 		char quote = line[size++];
// 		while (line[size] && line[size] != quote)
// 			size++;
// 		size -= 1;
// 	}
// //<

// 	if (!(size - *i))
// 		return (SUCCESS);
// 	str = malloc(sizeof(char) * (size - *i + 1));
// 	if (!str)
// 		return (FAILURE);
// 	size = 0;
// 	while (line[*i] && !is_separator(line[*i], esc_quote, *i))
// 	{
// 		str[size] = line[*i];
// 		size++;
// 		(*i)++;
// 	}

// //>
// 	if (line[*i] && (line[*i] == '\'' || line[*i] == '\"'))
// 	{
// 		char quote = line[(*i)++];
// 		while (line[*i] && line[*i] != quote)
// 		{
// 			str[size] = line[*i];
// 			size++;
// 			(*i)++;
// 		}
// 	}
// //<

// 	str[size] = 0;
// 	new = ft_lstnew(str);
// 	ft_lstadd_back(&(content->args), new);
// 	return (SUCCESS);
// }

// int short	state_default(t_cmd *content, char *line, int *i, int export, char **esc_quote)
// {
// 	if (*i == 0)
// 	{
// 		if (!pipe_at_begenning(content, line, i, export, esc_quote))
// 			return (FAILURE);
// 	}
// 	else
// 	{
// 		if (!regular_behavior(content, line, i, export, esc_quote))
// 			return (FAILURE);
// 	}
// 	return (SUCCESS);
// }
