/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 17:54:38 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:11:42 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_operator(char c)
{
	if (c == '|')
		return (1);
	if (c == ';')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '$')
		return (1);
	return (0);
}

int	is_operator(char *token, char next_char)
{
	if (ft_strlen(token) == 1 && is_first_operator(*token))
	{
		if (ft_isalnum(next_char) || ft_isspace(next_char))
			return (1);
	}
	if (!ft_strcmp(token, ">>"))
	{
		if (ft_isalnum(next_char) || ft_isspace(next_char))
			return (1);
	}
	return (0);
}
