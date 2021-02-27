/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:54:49 by bditte            #+#    #+#             */
/*   Updated: 2021/02/17 15:52:50 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_cmd *cmd, char **tokens, int first_tkn)
{
	(void)first_tkn;
	cmd->nb_cmds = 0;
	cmd->outfile = STDOUT_FILENO;
	cmd->infile = STDIN_FILENO;
	cmd->errfile = STDERR_FILENO;
	tokens += first_tkn;
	while (*tokens && (ft_strcmp(*tokens, ";") != 0))
	{
		if (!ft_strcmp(*tokens, "|"))
			cmd->nb_cmds++;
		tokens++;
	}
	cmd->nb_cmds++;
	cmd->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmd->nb_cmds);
	if (!cmd->simple_cmds)
		print_error_and_exit();
	cmd->curr_cmd = 0;
}

void	parse_command(t_parser *p, char **tokens)
{
	t_cmd	cmd;
	int		i;

	init_cmd(&cmd, tokens, p->first_tkn);
	i = -1;
	printf("current cmd : %d\n", p->curr_cmd);
	printf("nb simple_commands : %d\n", cmd.nb_cmds);
	while (++i < cmd.nb_cmds)
	{
		cmd.first_tkn = get_first_token(tokens, cmd.curr_cmd, '|');
		printf("simple command %d first token : %d\n", cmd.curr_cmd, p->first_tkn);
		parse_simple_command(tokens + p->first_tkn, cmd.first_tkn);
		cmd.curr_cmd++;
	}
	p->cmds[p->curr_cmd] = &cmd;
}