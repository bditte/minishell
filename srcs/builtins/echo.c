/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:20:20 by bditte            #+#    #+#             */
/*   Updated: 2021/02/24 15:32:21 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_echo(char **av)
{
	int	flag;
	int	i;

	if (!av[1])
	{
		printf("\n");
		return (0);	
	}
	if (!ft_strcmp(av[1], "-n") && !av[2])
		return (0);
	flag = !ft_strcmp(av[1], "-n");
	i = 0 + flag;
	while (av[++i])
		printf("%s ", av[i]);
	if (!flag)
		printf("\n");
	return (0);
}