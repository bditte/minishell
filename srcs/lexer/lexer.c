/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:13:38 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 15:13:25 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer_struct(t_lexer *lexer)
{
	if (!(lexer->buffer = malloc(sizeof(char) * BUF_SIZE)))
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
	if (!(lexer->buffer = malloc(sizeof(char) * BUF_SIZE)))
		print_error_and_exit();
}

void	join_char(t_lexer *lexer, char c)
{
	char	*tmp;

	if (lexer->position == lexer->buffsize - 1)
	{
		if (!(tmp = malloc(sizeof(char) * lexer->buffsize + BUF_SIZE)))
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

void		get_nb_tokens(t_lexer *lexer, char *line)
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
	if (!(lexer->tokens = malloc(sizeof(char *) * lexer->nb_tokens + 1)))	
		print_error_and_exit();
}

int lexer(t_lexer *lexer)
{
	char	**tokens;
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	tokens = NULL;
	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return (0);
	if (!ft_strcmp(line, "exit"))
	{
		free(line);
		lexer->nb_tokens = 0;
		return (INPUT_EXIT);
	}
	get_nb_tokens(lexer, line);
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
			add_new_token(lexer);
			reset_lexer_struct(lexer);
		}
	}
	free(lexer->buffer);
	free(line);
	lexer->tokens[lexer->nb_tokens] = 0;
	return (0);
}