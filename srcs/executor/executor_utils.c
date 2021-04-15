/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:46:05 by bditte            #+#    #+#             */
/*   Updated: 2021/04/09 09:43:37 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_path(char *cmd)
{
	char	path[6];
	char	*res;
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
	res = ft_strjoin(path, cmd);
	return (res);
}