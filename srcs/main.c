/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:33:06 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 18:11:49 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer, int exit_code)
{
	if (!lexer->nb_tokens)
		exit(1);
	while (--lexer->nb_tokens >= 0)
		free(lexer->tokens[lexer->nb_tokens]);
	free(lexer->tokens);
	if (exit_code)
		exit(1);
}

void	free_parser(t_parser *parser)
{
	if (parser->nb_cmds)
	{
		//while (--parser->nb_cmds >= 0)
		//	free(parser->cmds[parser->nb_cmds]);
		free(parser->cmds);
	}
}

int	main(void)
{
	t_lexer		l;
	t_parser	p;
	while (1)
	{
		print_prompt();
		if (lexer(&l) == INPUT_EXIT)
			free_lexer(&l, 1);
		parsing(&p, l.tokens);
		free_lexer(&l, 0);
		free_parser(&p);
		
	}
}
