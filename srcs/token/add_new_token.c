/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:50:58 by bditte            #+#    #+#             */
/*   Updated: 2021/02/13 16:17:07 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_token(t_lexer *l)
{
	l->tokens[l->current_token] = ft_strdup(l->buffer);
	l->current_token++;
	reset_lexer_struct(l);
}
