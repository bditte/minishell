/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:20:20 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 14:44:47 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_echo(char **av)
{
	int	flag;
	int	i;

	if (!av[1])
	{
		ft_putstr("\n");
		return (0);	
	}
	if (!ft_strcmp(av[1], "-n") && !av[2])
		return (0);
	flag = !ft_strcmp(av[1], "-n");
	i = 1 + flag;
	while (av[i])
	{
		ft_putstr(av[i++]);
		if (av[i])
			ft_putstr(" ");
	}
	if (!flag)
		ft_putstr("\n");
	return (0);
}