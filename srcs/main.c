/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:33:06 by bditte            #+#    #+#             */
/*   Updated: 2021/04/16 10:34:36 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lexer		l;
	t_rdc		*rdc;
	//t_parser	p;

	(void)argc;
	(void)argv;
	(void)envp;
	
	while (1)
	{
		rdc = malloc(sizeof(*rdc));
		if (!rdc)
			print_error_and_exit();
		print_prompt();
		if (lexer(&l) == INPUT_EXIT)
		{
			free(rdc);
			free_lexer(&l, 1);
		}
		parser(rdc, &(l.tokens), l.nb_tokens);
		free_lexer(&l, 0);
		executor(rdc, envp);
		free_ast(rdc);
	}
}
