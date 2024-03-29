/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:36:26 by bditte            #+#    #+#             */
/*   Updated: 2021/04/05 17:54:28 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_cd(char **av)
{
	if (av[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(av[1]) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}