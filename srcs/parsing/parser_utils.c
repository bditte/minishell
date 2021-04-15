/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:55:02 by bditte            #+#    #+#             */
/*   Updated: 2021/04/02 17:42:40 by bditte           ###   ########.fr       */
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
	rdc->tmp_node = malloc(sizeof(*rdc->tmp_node));
	if (!rdc->tmp_node)
		print_error_and_exit();
	*rdc->tmp_node = create_node(TMP_NODE, rdc, NULL);
	rdc->tmp_node->data = NULL;
	rdc->curr_root = malloc(sizeof(*rdc->curr_root));
	if (!rdc->curr_root)
		print_error_and_exit();
	*rdc->curr_root = create_node(CURR_ROOT, rdc, NULL);
	rdc->curr_root->data = NULL;
}

int	get_next_token(t_rdc *rdc)
{
	if (!rdc->tokens[rdc->i + 1])
	{
		rdc->is_last_token = 1;
		return (0);
	}
	rdc->i++;
	rdc->simple_i++;
	return (1);
}

void	assign_simple_command(t_rdc *rdc)
{
	rdc->curr_root->type = PIPESEQUENCE;
	rdc->curr_root->left = rdc->tmp_node->left;
	rdc->curr_root->left->parent = rdc->curr_root;
	rdc->tmp_node->left = NULL;
}

void	assign_complete_command(t_rdc *rdc)
{
	rdc->root->left = rdc->curr_root->left;
	rdc->root->left->parent = rdc->root;
	rdc->curr_root->left = NULL;
	rdc->curr_root->parent = NULL;
}
