/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 17:07:40 by bditte            #+#    #+#             */
/*   Updated: 2021/02/17 14:45:04 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_nb_cmds(char **tokens, t_parser *p)
{
	int	i;
	int j;

	j = 0;
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
	p->cmds = malloc(sizeof(t_cmd *) * p->nb_cmds);
	if (!p->cmds)
		print_error_and_exit();
	p->cmds[p->nb_cmds] = NULL;
	p->curr_cmd = -1;
}

int	parsing(t_parser *p, char **tokens)
{
	init_parser(p, tokens);
	while (++p->curr_cmd < p->nb_cmds)
	{
	
		p->first_tkn = get_first_token(tokens, p->curr_cmd, ';');
		parse_command(p, tokens);
	}
	return (0);
}