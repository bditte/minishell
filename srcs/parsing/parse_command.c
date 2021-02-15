/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:54:49 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 12:58:38 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_command(t_parser *p, t_lexer *l)
{
	t_cmd	*cmd;
	int		i;

	init_cmd();
	i = -1;
	while (++i < cmd->nb_cmds)
	{
		parse_simple_command();
	}
}