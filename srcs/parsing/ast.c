/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 17:07:34 by bditte            #+#    #+#             */
/*   Updated: 2021/04/05 16:05:08 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirect_type(char	*str)
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
	node.parent = parent;
	node.left = NULL;
	node.right = NULL;
	node.data = NULL;
	if (type <= ROOT)
		return (node);
	if (type == IO_REDIRECT)
		node.sub_type = get_redirect_type(rdc->tokens[rdc->i - 1]);
	node.parent = parent;
	node.data = ft_strdup(CURR_TOKEN);
	return (node);
}

void	new_right_node(int type, t_rdc *rdc, t_ast_node **p, t_ast_node **d)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		print_error_and_exit();
	*node = create_node(type, rdc, *p);
	if ((*p)->right)
	{
		node->right = (*p)->right;
		node->right->parent = node;
	}
	*d = node;
}

void	new_left_node(int type, t_rdc *rdc, t_ast_node **p, t_ast_node **d)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		print_error_and_exit();
	*node = create_node(type, rdc, *p);
	if ((*p)->left)
	{
		node->left = (*p)->left;
		node->left->parent = node;
	}
	*d = node;
}

void	new_right_child(int type, t_rdc *rdc, t_ast_node **p)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	node = malloc(sizeof(*node));
	if (!node)
		print_error_and_exit();
	*node = create_node(type, rdc, *p);
	if ((*p)->right)
	{
		tmp = (*p)->right;
		while (tmp->right)
			tmp = tmp->right;
		node->parent = tmp;
		tmp->right = node;
	}
	else
	{
		(*p)->right = node;
		node->parent = *p;
	}
}

void	new_left_child(int type, t_rdc *rdc, t_ast_node **p)
{
	t_ast_node	*node;
	t_ast_node	*tmp;

	node = malloc(sizeof(*node));
	if (!node)
		print_error_and_exit();
	*node = create_node(type, rdc, *p);
	if ((*p)->left)
	{
		tmp = (*p)->left;
		while (tmp->left)
			tmp = tmp->left;
		node->parent = tmp;
		tmp->left = node;
	}
	else
	{
		(*p)->left = node;
		node->parent = *p;
	}
}