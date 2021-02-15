/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:07:40 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 12:39:16 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_nb_cmds(char **tokens, t_parser *p)
{
	int	i;
	
	p->nb_cmds = 0;
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] == ';' && !tokens[i][1])
			p->nb_cmds++;
	}
	p->nb_cmds++;
}

void	init_parser(t_parser *p, char **tokens)
{
	get_nb_cmds(tokens, p);
	p->cmds = malloc(sizeof(t_simple_cmd *) * p->nb_cmds);
	if (!p->cmds)
		print_error_and_exit();
	p->cmds[p->nb_cmds] = NULL;
}

int	parsing(t_lexer *l, t_parser *p)
{
	//t_cmd	*cmd;
	int		i;

	init_parser(p, l->tokens);
	i = -1;
	while (++i < p->nb_cmds)
	{
			
	}
	return (0);
}