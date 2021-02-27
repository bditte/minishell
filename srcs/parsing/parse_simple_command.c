/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:59:00 by bditte            #+#    #+#             */
/*   Updated: 2021/02/24 15:19:22 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_simple_cmd(char **tokens, int first_tkn, t_mini_parser *m_parser)
{

	m_parser->nb_tkns = 0;
	while (tokens[first_tkn] && \
		ft_strcmp(tokens[first_tkn], "|") && \
		ft_strcmp(tokens[first_tkn], ";"))
	{
		m_parser->nb_tkns++;
		first_tkn++;
	}
	m_parser->curr_tkn = 0;

}

t_simple_cmd	*parse_simple_command(char **tokens, int first_tkn)
{
	t_simple_cmd	*cmd;
	t_mini_parser	m_parser;
	int				i;

	cmd = NULL;
	init_simple_cmd(tokens, first_tkn, &m_parser);
	printf("first tkn : %s nb tokens %d\n", tokens[first_tkn], m_parser.nb_tkns);
	i = -1;
/*	while (++i < cmd->nb_args)
	{
		//add argument
	}	*/
	return (cmd);
}