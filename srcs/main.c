/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:33:06 by bditte            #+#    #+#             */
/*   Updated: 2021/02/12 17:04:43 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_everything(t_lexer *lexer, int exit_code)
{
	if (!lexer->nb_tokens)
		exit(1);
	while (--lexer->nb_tokens >= 0)
		free(lexer->tokens[lexer->nb_tokens]);
	free(lexer->tokens);
	if (exit_code)
		exit(1);
}

int main(void)
{
	t_lexer	l;
	while (1)
	{
		print_prompt();
		if (lexer(&l) == INPUT_EXIT)
			free_everything(&l, 1);
		else
			free_everything(&l, 0);
		
	}
}