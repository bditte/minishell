/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:13:38 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 17:01:15 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isspace(lexer->line[i]) && !lexer->quoted)
			continue ;
		join_char(lexer, lexer->line[i]);
		if (token_recognition(lexer, lexer->line[i + 1]))
			add_new_token(lexer);
	}
	free(lexer->buffer);
	free(lexer->line);
//	for (int i = 0; i < lexer->nb_tokens; i++)
//		printf("token %d :|%s|\n", i, lexer->tokens[i]);
	return (0);
}
