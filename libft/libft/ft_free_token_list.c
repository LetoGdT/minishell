/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:46:22 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/06/22 19:30:05 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_free_token_list(char **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		free(token_list[i++]);
	free(token_list);
}
