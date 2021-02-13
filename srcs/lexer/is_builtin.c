/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:40:17 by bditte            #+#    #+#             */
/*   Updated: 2021/02/09 12:30:31 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *token, char next_char)
{
	if (!ft_isspace(next_char) && next_char != 0)
		return (0);
	if (!ft_strcmp(token, "echo"))
		return (1);
	if (!ft_strcmp(token, "cd"))
		return (1);
	if (!ft_strcmp(token, "pwd"))
		return (1);
	if (!ft_strcmp(token, "export"))
		return (1);
	if (!ft_strcmp(token, "unset"))
		return (1);
	if (!ft_strcmp(token, "exit"))
		return (1);
	if (!ft_strcmp(token, "env"))
		return (1);
	return (0);
}