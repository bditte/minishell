/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:59:00 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 13:00:39 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_simple_command()
{
	t_simple_cmd	*cmd;
	int				i;

	init_simple_cmd();
	i = -1;
	while (++i < cmd->nb_args)
	{
		//add argument
	}	
}