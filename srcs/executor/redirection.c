/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:40:01 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 14:35:44 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_infile(t_exec *exec, t_ast_node *node)
{
	exec->infile = open(node->data, O_RDWR, 0666);
	if (exec->infile < 0)
		return (print_errno("open"));
	return (0);
}

int	close_existing_fd(t_exec *exec, t_ast_node *node)
{
	if (node->sub_type != TYPE_LESS && exec->outfile > 0)
	{
		if (ft_close(exec->outfile))
			return (1);
	}
	else if (node->sub_type == TYPE_LESS && exec->infile > 0)
	{
		if (ft_close(exec->infile))
			return (1);
	}
	return (0);
}

int	get_left(t_exec	*exec, t_ast_node *node)
{
	while (node->left)
	{
		node = node->left;
		if (node->type == IO_REDIRECT)
		{
			if (close_existing_fd(exec, node))
				return (1);
			if (node->sub_type == TYPE_GREAT)
			{
				exec->outfile = open(node->data, 0100 | 01 | 01000, 0666);
				if (exec->outfile < 0)
					return (print_errno("open"));
			}
			else if (node->sub_type == TYPE_DGREAT)
			{
				exec->outfile = open(node->data, 0100 | 01 | 02000, 0666);
				if (exec->outfile < 0)
					return (print_errno("open"));
			}
			else
				if (assign_infile(exec, node))
					return (1);
		}
	}
	return (0);
}

int	get_right(t_exec *exec, t_ast_node *node)
{
	while (node->right)
	{
		node = node->right;
		if (node->type == IO_REDIRECT)
		{
			if (close_existing_fd(exec, node))
				return (1);
			if (node->sub_type == TYPE_GREAT)
			{
				exec->outfile = open(node->data, 0100 | 01 | 01000, 0666);
				if (exec->outfile < 0)
					return (print_errno("open"));
			}
			else if (node->sub_type == TYPE_DGREAT)
			{
				exec->outfile = open(node->data, 0100 | 01 | 02000, 0666);
				if (exec->outfile < 0)
					return (print_errno("open"));
			}
			else
				if (assign_infile(exec, node))
					return (1);
		}
	}
	return (0);
}

int	get_redirections(t_exec	*exec, t_ast_node *node)
{
	exec->outfile = -1;
	exec->infile = -1;
	exec->ret = 0;
	node = node->left;
	if (get_left(exec, node))
		return (1);
	if (get_right(exec, node))
		return (1);
	exec->fdin = dup(STDIN_FILENO);
	node = node->parent;
	if (init_fd(exec, node))
		return (1);
	return (0);
}
