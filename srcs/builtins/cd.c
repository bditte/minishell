/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:36:26 by bditte            #+#    #+#             */
/*   Updated: 2021/02/24 16:25:40 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_cd(char **av)
{
	if (av[2])
	{
		builtin_error("cd: too many arguments");
		return (1);
	}
	if (chdir(av[1]) == -1)
	{
		builtin_strerror("cd");
		return (1);
	}
	return (0);
}