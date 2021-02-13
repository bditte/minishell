/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:56:54 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:10:17 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_char(t_lexer *lexer, char c)
{
	char	*tmp;

	if (lexer->position == lexer->buffsize - 1)
	{
		tmp = malloc(sizeof(char) * lexer->buffsize + BUF_SIZE);
		if (!tmp)
			print_error_and_exit();
		lexer->buffsize += BUF_SIZE;
		ft_strlcpy(tmp, lexer->buffer, lexer->position + 1);
		free(lexer->buffer);
		lexer->buffer = tmp;
	}
	lexer->buffer[lexer->position] = c;
	lexer->buffer[lexer->position + 1] = 0;
	lexer->position++;
}

void	handle_quote(t_lexer *lexer, char *line, int i)
{
	if (ft_isquote(line[i]) && !lexer->quoted)
		lexer->quoted = line[i];
	else if (ft_isquote(line[i]) && lexer->quoted == line[i])
		lexer->quoted = 0;
}
