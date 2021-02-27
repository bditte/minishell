/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:12:56 by bditte            #+#    #+#             */
/*   Updated: 2021/02/24 15:50:33 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_and_exit(void)
{
	printf("minishell: %s\n", strerror(errno));
	exit(0);
}

void	builtin_error(char *str)
{
	printf("minishell: %s\n", str);
	exit(0);
}

void	builtin_strerror(char *builtin)
{
	printf("minishell: %s: %s\n,", builtin, strerror(errno));	
}
