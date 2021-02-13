/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:13:38 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:07:42 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isquote(line[i]) && !lexer->quoted)
			lexer->quoted = line[i];
		else if (ft_isquote(line[i]) && lexer->quoted == line[i])
			lexer->quoted = 0;
		if (ft_isspace(line[i]) && !lexer->quoted)
			continue ;
		join_char(lexer, line[i]);
		if (token_recognition(lexer, line[i + 1]))
		{
			lexer->nb_tokens++;
			reset_lexer_struct(lexer);
		}
	}
	lexer->tokens = malloc(sizeof(char *) * lexer->nb_tokens + 1);
	if (!lexer->tokens)
		print_error_and_exit();
	lexer->tokens[lexer->nb_tokens] = 0;
}

int	lexer(t_lexer *lexer)
{
	int		i;

	i = -1;
	lexer->line = NULL;
	if (get_next_line(STDIN_FILENO, &lexer->line) <= 0)
		return (0);
	if (!ft_strcmp(lexer->line, "exit"))
	{
		free(lexer->line);
		lexer->nb_tokens = 0;
		return (INPUT_EXIT);
	}
	get_nb_tokens(lexer, lexer->line);
	while (lexer->line[++i])
	{
		handle_quote(lexer, lexer->line, i);
		if (ft_isspace(lexer->line[i]) && !lexer->quoted)
			continue ;
		join_char(lexer, lexer->line[i]);
		if (token_recognition(lexer, lexer->line[i + 1]))
			add_new_token(lexer);
	}
	free(lexer->buffer);
	free(lexer->line);
	return (0);
}
