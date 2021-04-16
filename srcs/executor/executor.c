/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:24:05 by bditte            #+#    #+#             */
/*   Updated: 2021/04/16 10:37:24 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipesequence(t_ast_node *root, t_exec *exec, t_rdc *rdc)
{
	t_ast_node	*node;
	int			ret;

	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	node = root->left;
	while (node)
	{

		if (get_redirections(exec, node))
			return (1);
		exec->args = get_cmd_args(node->left);
		if (!exec_builtin(exec))
			node = node->right;
		else
		{	
			ret = fork();
			if (ret == 0)
			{
				if (!is_cmd(exec->args[0], &(exec->cmd)))
					printf("%s : command not found\n", exec->args[0]);
				else if (execve(exec->cmd, exec->args, exec->envp) < 0)
					printf("%s : %s\n", exec->args[0], strerror(errno));
				exit_fork(exec, rdc);
			}
			else if (ret < 0)
			{
				free_tab(exec->args);
				return (print_errno("fork"));
			}
			else
			{	
				wait(NULL);
				free_tab(exec->args);
				node = node->right;
			}
		}
	}
	if (reset_fd(exec))
		return (1);
	return (0);
}

int	exec_complete_cmd(t_ast_node *root, t_exec *exec, t_rdc *rdc)
{
	t_ast_node	*node;

	node = root->left;
	while (node)
	{
		if (check_redirections(node->left, exec))
			node = node->right;
		else
		{
			if (exec_pipesequence(node, exec, rdc))
				return (1);
			node = node->right;
		}
	}
	return (0);
}

int	executor(t_rdc *rdc, char **envp)
{
	t_exec	exec;

	exec.rdc = rdc;
	exec.envp = envp;
	if (exec_complete_cmd(rdc->root, &exec, rdc))
		return (1);
	return (0);
}