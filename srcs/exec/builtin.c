/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:13:25 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/09/28 18:13:49 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



	static const t_builtin fun_list[5] = [
		{"cd", 0, ft_cd},
		{"pwd", 1, ft_pwd},
		{"export", 0, ft_export},
		{"unset", 0, ft_unset},
		{"env", 1, ft_env}];




