/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:07:34 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:46:59 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_redirect_type(char	*str)
{
	if (!ft_strcmp(str, LESS))
		return (TYPE_LESS);
	if (!ft_strcmp(str, GREAT))
		return (TYPE_GREAT);
	return (TYPE_DGREAT);
}

t_ast_node	create_node(int type, t_rdc *rdc, t_ast_node *parent)
{
	t_ast_node	node;

	node.type = type;
	node.left = NULL;
	node.right = NULL;
	if (type == ROOT || type == TMP_NODE)
		return (node);
	if (type == IO_REDIRECT)
		node.sub_type = get_redirect_type(rdc->tokens[rdc->i - 1]);
	node.parent = parent;
	node.data = ft_strdup(CURR_TOKEN);
	return (node);
}

void	new_node(int type, t_rdc *rdc, t_ast_node **parent, t_ast_node **dest)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		print_error_and_exit();
	*node = create_node(type, rdc, *parent);
	if ((*parent)->left)
	{
		node->left = (*parent)->left;
		node->left->parent = node;
	}
	*dest = node;
}
