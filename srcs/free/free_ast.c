/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:46:26 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 23:24:50 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_simplecommand(t_ast_node *node)
{
	node = node->left;
	if (node->left)
		free_left_children(node);
	node->left = NULL;
	if (node->right)
		free_right_children(node);
	node->right = NULL;
	if (node->data)
		free(node->data);
	free(node);
}

void	free_pipesequence(t_ast_node *node)
{
	t_ast_node	*parent;

	node = node->left;
	while (node->right)
		node = node->right;
	while (node->parent->type != COMPLETE_COMMAND)
	{
		free_simplecommand(node);
		parent = node->parent;
		if (node->data)
			free(node->data);
		free(node);
		node = parent;
	}
	free_simplecommand(node);
	if (node->data)
		free(node->data);
	free(node);
	
}

void	free_completecommands(t_ast_node *node)
{
	t_ast_node	*parent;

	while (node->right)
		node = node->right;
	while (node->parent->type != ROOT)
	{
		free_pipesequence(node);
		parent = node->parent;
		if (node->data)
			free(node->data);
		free(node);
		node = parent;
	}
	free_pipesequence(node);
	if (node->data)
			free(node->data);
	free(node);
}

void	free_ast(t_rdc *rdc)
{
	t_ast_node *node;

	node = rdc->root->left;
	free_completecommands(node);
	free(rdc->root);
	free(rdc);
}