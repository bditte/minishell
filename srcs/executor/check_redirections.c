/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:25:48 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 11:08:45 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fd(t_exec *exec)
{
	if (exec->outfile > 0)
	{
		if (ft_close(exec->outfile))
			return (1);
	}
	if (exec->infile > 0)
	{
		if (ft_close(exec->infile))
			return (1);
	}
	exec->outfile = -1;
	exec->infile = -1;
	return (0);
}

int	check_infile(t_exec *exec, t_ast_node *node)
{
	exec->infile = open(node->data, O_RDWR, 0666);
	if (exec->infile < 0)
		return (print_errno(node->data));
	return (0);
}

int	check_right_io(t_ast_node *node, t_exec *exec)
{
	while (node->right)
	{
		node = node->right;
		close_fd(exec);
		if (node->type == IO_REDIRECT)
		{
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
				if (check_infile(exec, node))
					return (1);
		}
	}
	return (0);
}

int	check_left_io(t_ast_node *node, t_exec *exec)
{
	while (node->left)
	{
		node = node->left;
		close_fd(exec);
		if (node->type == IO_REDIRECT)
		{
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
				if (check_infile(exec, node))
					return (1);
		}
	}
	return (0);
}

int	check_redirections(t_ast_node *node, t_exec *exec)
{
	t_ast_node	*parent;
	int			ret;

	ret = 0;
	while (node->right)
		node = node->right;
	parent = node;
	while (node->type != COMPLETE_COMMAND)
	{
		exec->outfile = -1;
		exec->infile = -1;
		parent = node;
		node = node->left;
		if (check_left_io(node, exec))
			ret = 1;
		exec->outfile = -1;
		exec->infile = -1;
		if (check_right_io(node, exec))
			ret = 1;
		node = parent->parent;
	}
	return (ret);
}
