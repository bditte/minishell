/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:53:06 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 14:35:38 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_fd(t_exec *exec)
{
	if (dup2(exec->tmpin, STDIN_FILENO) < 0)
		return (print_errno("dup2"));
	if (dup2(exec->tmpout, STDOUT_FILENO) < 0)
		return (print_errno("dup2"));
	if (close(exec->tmpin) < 0)
		return (print_errno("close"));
	if (close(exec->tmpout) < 0)
		return (print_errno("close"));
	return (0);
}

int	assign_fdout(t_exec *exec)
{
	if (dup2(exec->fdout, STDOUT_FILENO) < 0)
		return (print_errno("dup2"));
	if (close(exec->fdout) < 0)
		return (print_errno("close"));
	return (0);
}

int	init_fd(t_exec *exec, t_ast_node *node)
{
	if (exec->infile > 0)
		exec->fdin = exec->infile;
	if (dup2(exec->fdin, STDIN_FILENO) < 0)
		return (print_errno("dup2"));
	if (close(exec->fdin) < 0)
		return (print_errno("close"));
	if (node->right)
	{
		if (pipe(exec->fdpipe) < 0)
			return (print_errno("pipe"));
		exec->fdin = exec->fdpipe[0];
		if (exec->outfile > 0)
			exec->fdout = exec->outfile;
		else
			exec->fdout = exec->fdpipe[1];
	}
	else
	{
		if (exec->outfile > 0)
			exec->fdout = exec->outfile;
		else
			exec->fdout = dup(exec->tmpout);
	}
	return (assign_fdout(exec));
}
