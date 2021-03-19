/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:33:06 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:43:20 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_lexer		l;
	t_rdc		rdc;
	//t_parser	p;

	while (1)
	{
		print_prompt();
		if (lexer(&l) == INPUT_EXIT)
			free_lexer(&l, 1);
		parser(&rdc, &(l.tokens), l.nb_tokens);
		//parsing(&p, l.tokens);
		free_parser(&rdc);
		free_lexer(&l, 0);
		
	}
}
