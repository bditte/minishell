/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:00:40 by bditte            #+#    #+#             */
/*   Updated: 2021/04/16 10:37:13 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fork(t_exec *exec, t_rdc *rdc)
{
	free(exec->cmd);
	free_tab(exec->args);
	free_ast(rdc);
	exit(1);
}