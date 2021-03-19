/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:06:59 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:49:01 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tree(t_ast_node *root)
{
	int			i;
	t_ast_node	*node;
	
	i = 0;
	node = root->left;
	printf("ROOT NODE %d type %d\n", i, root->type);
	i++;
	while (node)
	{
		printf("NODE %d TYPE %d DATA %s\n", i, node->type, node->data);
		printf("NODE %d PARENT_TYPE %d PARENT_DATA %s\n", i, node->parent->type, node->parent->data);
		node = node->left;
		i++;
	}
	printf("END OF TREE\n");
}