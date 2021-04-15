/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:12:35 by bditte            #+#    #+#             */
/*   Updated: 2021/04/03 17:41:28 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bash_pwd(char **av)
{
	char	*buf;
	int		size;

	(void)av;
	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	if (!buf)
	{
		builtin_strerror("pwd");
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}