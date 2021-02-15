/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:55:02 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 12:02:08 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_arg(t_simple_cmd *cmd, char *arg)
{
	if (cmd->nb_available_args < cmd->nb_args)
	{
		cmd->args[cmd->nb_args - 1] = arg;
		cmd->nb_args++;
		return (1);
	}
	return (0);
}

int	insert_cmd(t_cmd *cmd, t_simple_cmd *s_cmd)
{
	if (cmd->nb_available_cmds < cmd->nb_cmds)
	{
		cmd->simple_cmds[cmd->nb_cmds - 1] = s_cmd;
		cmd->nb_cmds++;
		return (1);
	}
	return (0);
}