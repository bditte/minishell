/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 19:10:55 by bditte            #+#    #+#             */
/*   Updated: 2021/04/05 12:36:31 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	while (--i >= 0)
		free(args[i]);
	free(args);
}