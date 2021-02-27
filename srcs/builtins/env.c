/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:41:11 by bditte            #+#    #+#             */
/*   Updated: 2021/02/24 16:45:54 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_env(char **av, char **envp)
{
	int	i;

	if (av[1])
	{
		builtin_error("env: too many arguments");
		return (1);
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}