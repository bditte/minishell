/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:55:02 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:45:04 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(t_rdc *rdc, int nb_tokens)
{
    rdc->i = 0;
	rdc->nb_tokens = nb_tokens;
	rdc->is_last_token = 0;
	rdc->root = malloc(sizeof(*rdc->root));
	if (!rdc->root)
		print_error_and_exit();
	*rdc->root = create_node(ROOT, rdc, NULL);
	rdc->root->data = NULL;
/*	rdc->tmp_node = malloc(sizeof(*rdc->tmp_node));
	if (!rdc->tmp_node)
		print_error_and_exit();
	*rdc->tmp_node = create_node(ROOT, rdc, NULL);
	rdc->tmp_node->data = NULL;*/
}