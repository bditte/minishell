/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 15:56:54 by bditte            #+#    #+#             */
/*   Updated: 2021/03/18 14:54:22 by bditte           ###   ########.fr       */
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

void	init_lexer_struct(t_lexer *lexer)
{
	lexer->buffer = malloc(sizeof(char) * BUF_SIZE);
	if (!lexer->buffer)
		print_error_and_exit();
	lexer->position = 0;
	lexer->quoted = 0;
	lexer->nb_tokens = 0;
	lexer->current_token = 0;
	lexer->buffsize = BUF_SIZE;
}

void	reset_lexer_struct(t_lexer *lexer)
{
	lexer->position = 0;
	lexer->buffsize = BUF_SIZE;
	lexer->quoted = 0;
	free(lexer->buffer);
	lexer->buffer = malloc(sizeof(char) * BUF_SIZE);
	if (!lexer->buffer)
		print_error_and_exit();
}

void	get_nb_tokens(t_lexer *lexer, char *line)
{
	int	i;

	i = -1;
	init_lexer_struct(lexer);
	while (line[++i])
	{
		if (ft_isspace(line[i]) && !lexer->quoted)
			continue ;
		join_char(lexer, line[i]);
		if (token_recognition(lexer, line[i + 1]))
		{	
			lexer->nb_tokens++;
			reset_lexer_struct(lexer);
		}
	}
	lexer->tokens = malloc(sizeof(char *) * (lexer->nb_tokens + 1));
	if (!lexer->tokens)
		print_error_and_exit();
	lexer->tokens[lexer->nb_tokens] = 0;
}
