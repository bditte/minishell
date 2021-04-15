/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:40:15 by bditte            #+#    #+#             */
/*   Updated: 2021/04/03 18:58:20 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_left_children(t_ast_node *node)
{
	t_ast_node *parent;

	while (node->left)
		node = node->left;
	parent = node->parent;
	while (parent->type != CMD_NAME && parent->type != CMD_WORD)
	{
		parent = node->parent;
		if (node->data)
			free(node->data);
		free(node);
		node = parent;
		parent = node->parent;
	}
	if (node->data)
			free(node->data);
	free(node);
}

void	free_right_children(t_ast_node *node)
{
	t_ast_node *parent;

	while (node->right)
		node = node->right;
	parent = node->parent;
	while (parent->type != CMD_NAME && parent->type != CMD_WORD)
	{
		parent = node->parent;
		if (node->data)
			free(node->data);
		free(node);
		node = parent;
		parent = node->parent;
	}
	if (node->data)
			free(node->data);
	free(node);
	node = parent;
}