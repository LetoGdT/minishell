/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sapce_and_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:33:39 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 16:33:44 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

short int	is_space_and_next(char *str, int i, char c)
{
	return ((str[i] == c && str[i + 1] && str[i + 1] == c));
}