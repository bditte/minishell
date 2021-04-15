/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 15:24:05 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 14:35:32 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipesequence(t_ast_node *root, t_exec	*exec)
{
	t_ast_node	*node;
	char		**args;
	char		*cmd;
	int			ret;

	exec->tmpin = dup(STDIN_FILENO);
	exec->tmpout = dup(STDOUT_FILENO);
	node = root->left;
	while (node)
	{
		if (get_redirections(exec, node))
			return (1);
		args = get_cmd_args(node->left);
		if (is_builtin(args[0]))
		{
		/*	exec->outfile = open("out", 0100 | 01 | 01000, 0666);
			dup2(exec->outfile, STDOUT_FILENO);*/
			exec_builtin(args[0], args);
			free_tab(args);
			node = node->right;
		}
		else
		{		
			ret = fork();
			if (ret == 0)
			{
				cmd = add_path(args[0]);
				if (execve(cmd, args, exec->envp) < 0)
				{
					if (errno == 2)
						printf("%s : command not found\n", args[0]);
					else
						printf("%s : %s\n", args[0], strerror(errno));
				}
				free(cmd);
				exit(1);
			}
			else if (ret < 0)
			{
				free_tab(args);
				return (print_errno("fork"));
			}
			else
			{	
				wait(NULL);
				free_tab(args);
				node = node->right;
			}
		}
	}
	if (reset_fd(exec))
		return (1);
	return (0);
}

int	exec_complete_cmd(t_ast_node *root, t_exec *exec)
{
	t_ast_node	*node;

	node = root->left;
	while (node)
	{
		if (check_redirections(node->left, exec))
			node = node->right;
		else
		{
			if (exec_pipesequence(node, exec))
				return (1);
			node = node->right;
		}
	}
	return (0);
}

int	executor(t_ast_node *root, char **envp)
{
	t_exec	exec;

	exec.envp = envp;
	if (exec_complete_cmd(root, &exec))
		return (1);
	return (0);
}