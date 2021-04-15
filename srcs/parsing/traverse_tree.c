/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:06:59 by bditte            #+#    #+#             */
/*   Updated: 2021/03/31 15:22:58 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_right_children(t_ast_node *root)
{
	t_ast_node *node;
	int			i;

	i = 0;
	node = root;
	while (node)
	{
		printf("NODE %d TYPE %d DATA %s\n", i, node->type, node->data);
		if (node->right)
			node = node->right;
		else if (node->left)
			node = node->left;
		else
			node = NULL;
		i++;
		if (i > 4)
			exit(1);
	}
	printf("END OF RIGHT CHILDREN\n");
}

void	display_tree(t_ast_node *root)
{
	int			i;
	t_ast_node	*node;
	
	i = 0;
	node = root;
	printf("ROOT NODE %d type %d\n", i, root->type);
	i++;
	while (node)
	{
		printf("NODE %d TYPE %d DATA %s\n", i, node->type, node->data);
		if (node->right)
		{
			printf("CMD RIGHT CHILDREN\n");
			display_right_children(node->right);
		}
		if (node->type && node->type != PIPESEQUENCE)
			printf("PARENT %d PARENT_TYPE %d PARENT_DATA %s\n", i, node->parent->type, node->parent->data);
		node = node->left;
		i++;
	}
	printf("END OF TREE\n");
}