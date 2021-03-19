/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:51:21 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:44:11 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer, int exit_code)
{
	if (!lexer->nb_tokens)
		exit(1);
	while (--lexer->nb_tokens >= 0)
	{
		if (*lexer->tokens[lexer->nb_tokens])
			free(lexer->tokens[lexer->nb_tokens]);
	}
	free(lexer->tokens);
	if (exit_code)
		exit(1);
}

void	free_parser(t_rdc *rdc)
{
	free_ast(rdc->root);
	printf("AST FREED\n");
/*	free(rdc->tokens);
	free(rdc);*/
}
