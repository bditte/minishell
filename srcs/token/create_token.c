/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:07:57 by bditte            #+#    #+#             */
/*   Updated: 2021/02/08 13:01:33 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	create_token(char *value, int type)
{
	t_token res;
	int		len;

	len = ft_strlen(value);
	if (!(res.value = malloc(sizeof(char) * len + 1)))
		exit(0);
	ft_memcpy(res.value, value, len);
	res.value[len] = 0;
	res.type = type;
	return (res);
}