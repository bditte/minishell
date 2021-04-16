/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:40:17 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 23:18:53 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "echo"))
		return (1);
	/*if (!ft_strcmp(token, "cd"))
		return (1);
	if (!ft_strcmp(token, "pwd"))
		return (1);
	if (!ft_strcmp(token, "export"))
		return (1);
	if (!ft_strcmp(token, "unset"))
		return (1);
	if (!ft_strcmp(token, "exit"))
		return (1);
	if (!ft_strcmp(token, "env"))
		return (1);*/
	return (0);
}

int	exec_builtin(t_exec *exec)
{
	if (!is_builtin(exec->args[0]))
		return (1);
	if (!ft_strcmp(exec->args[0], "echo"))
		bash_echo(exec->args);
/*	if (!ft_strcmp(name, "cd"))
		bash_cd(args);
	if (!ft_strcmp(name, "pwd"))
		bash_pwd(args);
	if (!ft_strcmp(name, "export"))
		bash_export(args);
	if (!ft_strcmp(name, "unset"))
		bash_unset(args);
	if (!ft_strcmp(name, "exit"))
		bash_exit(args);
	if (!ft_strcmp(name, "env"))
		bash_env(args);*/
	free_tab(exec->args);
	return (0);
}
