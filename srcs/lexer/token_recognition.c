/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:10:42 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_recognition(t_lexer *l, char next_char)
{
	int	len;

	len = ft_strlen(l->buffer);
	if (!next_char)
		return (1);
	if (!l->quoted)
	{
		if (is_first_operator(next_char) && *l->buffer != '>')
			return (1);
		if (is_builtin(l->buffer, next_char))
			return (1);
		if (is_operator(l->buffer, next_char))
			return (1);
		if (ft_isspace(next_char))
			return (1);
	}
	if (l->buffer[len - 1] == '\\' && !l->quoted)
	{
		l->buffer[len - 1] = next_char;
		return (1);
	}
	return (0);
}
