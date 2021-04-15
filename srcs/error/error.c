/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:12:56 by bditte            #+#    #+#             */
/*   Updated: 2021/04/14 14:36:11 by bditte           ###   ########.fr       */
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

int	print_errno(char *str)
{
	printf("minishell: %s: %s\n", str, strerror(errno));
	return (1);
}

void	builtin_strerror(char *builtin)
{
	printf("minishell: %s: %s\n,", builtin, strerror(errno));	
}
