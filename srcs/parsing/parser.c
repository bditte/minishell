/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:47:16 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 18:35:47 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_command(t_rdc *rdc)
{
	rdc->simple_i = 0;
	if (cmd_prefix(rdc))
	{
		if (!rdc->is_last_token)
		{
			if (cmd_word(rdc))
			{
				new_left_node(CMD_WORD, rdc, &rdc->tmp_node, &rdc->tmp_node->left);
				get_next_token(rdc);
			}
		}
	}
	else
	{
		if (cmd_name(rdc))
		{
			new_left_node(CMD_NAME, rdc, &rdc->tmp_node, &rdc->tmp_node->left);
			get_next_token(rdc);
		}
	}
	if (!rdc->is_last_token)
		cmd_suffix(rdc);
	return (1);
}

int	pipesequence(t_rdc *rdc)
{
	if (simple_command(rdc))
	{
		if (rdc->curr_root->left)
		{
			new_right_node(PIPESEQUENCE, rdc, &rdc->curr_root,
				&rdc->curr_root->right);
			rdc->curr_root = rdc->curr_root->right;
		}
		else
		{
			new_left_node(PIPESEQUENCE, rdc, &rdc->curr_root, &rdc->curr_root->left);
			rdc->curr_root = rdc->curr_root->left;
		}
		assign_simple_command(rdc);
		if (!ft_strcmp(CURR_TOKEN, "|"))
		{
			if (get_next_token(rdc))
				pipesequence(rdc);
			return (1);
		}
		while (rdc->curr_root->parent)
			rdc->curr_root = rdc->curr_root->parent;
		return (1);
	}
	return (0);
}

int	complete_commands(t_rdc *rdc)
{
	if (pipesequence(rdc))
	{
		if (rdc->root->left)
		{
			new_right_node(COMPLETE_COMMAND, rdc, &rdc->root, &rdc->root->right);
			rdc->root = rdc->root->right;
		}
		else
		{
			new_left_node(COMPLETE_COMMAND, rdc, &rdc->root, &rdc->root->left);
			rdc->root = rdc->root->left;
		}
		assign_complete_command(rdc);
		if (!ft_strcmp(CURR_TOKEN, ";"))
		{
			if (get_next_token(rdc))
				complete_commands(rdc);
			return (1);
		}
		while (rdc->root->type != ROOT)
			rdc->root = rdc->root->parent;
		return (1);
	}
	return (0);
}

int	parser(t_rdc *rdc, char ***tokens, int nb_tokens)
{
	init_parser(rdc, nb_tokens);
	rdc->tokens = *tokens;
	complete_commands(rdc);
	free(rdc->curr_root);
	free(rdc->tmp_node);
	/*display_tree(rdc->root);
	exit(1);*/
	return (0);
}
