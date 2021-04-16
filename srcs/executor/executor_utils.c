/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:46:05 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 21:20:02 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd2(char *cmd, char **res)
{
	struct	stat buf;
	char	path[10];
	int		i;

	i = 0;
	path[0] = '/';
	path[1] = 'u';
	path[2] = 's';
	path[3] = 'r';
	path[4] = '/';
	path[5] = 'b';
	path[6] = 'i';
	path[7] = 'n';
	path[8] = '/';
	path[9] = '\0';
	while (cmd[i])
		i++;
	*res = ft_strjoin(path, cmd);
	if (stat(*res, &buf) == 0)
		return (1);
	return (0);
}

int	is_cmd(char *cmd, char **res)
{
	struct	stat buf;
	char	path[6];
	int		i;

	i = 0;
	path[0] = '/';
	path[1] = 'b';
	path[2] = 'i';
	path[3] = 'n';
	path[4] = '/';
	path[5] = '\0';
	while (cmd[i])
		i++;
	*res = ft_strjoin(path, cmd);
	if (stat(*res, &buf) == 0)
		return (1);
	free(*res);
	return (is_cmd2(cmd, res));
}