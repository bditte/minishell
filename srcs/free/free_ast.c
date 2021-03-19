/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:46:26 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:49:30 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast_node *root)
{
	t_ast_node *node;
	t_ast_node *parent;

	parent = NULL;
	node = root;
	while (node->left)
	{
		node = node->left;
	}
	printf("ENTERING FREE MODE\n");
	while (node->type != ROOT)
	{
		parent = node->parent;
		if (node->data)
			free(node->data);
		free(node);
		node = parent;
	}
	free(root);
	printf("SUCCESS FREE\n");
}