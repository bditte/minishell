/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:06:56 by bditte            #+#    #+#             */
/*   Updated: 2021/02/16 15:33:58 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(t_lexer *l, char next_char, int len)
{
	if (l->buffer[len - 1] == '\\' && !l->quoted)
	{
		l->buffer[len - 1] = next_char;
		l->i++;	
	}
	if (ft_isquote(next_char) && !l->quoted)
		return (1);
	if (ft_isquote(l->buffer[len - 1]))
	{
		if (!l->quoted)
			l->quoted = l->buffer[len - 1];
		else if (l->quoted == l->buffer[len - 1])
		{
			l->quoted = 0;
			return (1);
		}
	}
	return (0);
}

int	token_recognition(t_lexer *l, char next_char)
{
	int	len;

	len = ft_strlen(l->buffer);
	if (!next_char)
		return (1);
	if (handle_quote(l, next_char, len))
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
		if (ft_isquote(next_char))
			return (1);
	}
	return (0);
}
