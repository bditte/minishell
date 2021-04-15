/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 17:07:37 by bditte            #+#    #+#             */
/*   Updated: 2021/04/14 22:47:21 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_redirect(t_rdc *rdc)
{
	if (!ft_strcmp(CURR_TOKEN, LESS) || !ft_strcmp(CURR_TOKEN, GREAT)
		|| !ft_strcmp(CURR_TOKEN, DGREAT))
	{
		if (!get_next_token(rdc))
			return (0);
		if (cmd_word(rdc)) //check rule 2
			return (1);
	}
	return (0);
}

int	cmd_word(t_rdc *rdc)
{
	//ajouter handle = 
	if (ft_strcmp(CURR_TOKEN, PIPE) && ft_strcmp(CURR_TOKEN, SEMICOLON)
		&& *CURR_TOKEN)
		return (1);
	return (0);
}

int	cmd_name(t_rdc *rdc)
{
	//ajouter handle =
	if (rdc->simple_i == 0)
		return (1);
	return (0);
}

int	cmd_suffix(t_rdc *rdc)
{
	if (io_redirect(rdc))
	{
		new_right_child(IO_REDIRECT, rdc, &rdc->tmp_node->left);
		if (get_next_token(rdc))
			cmd_suffix(rdc);
		return (1);
	}
	if (ft_strcmp(CURR_TOKEN, PIPE) && ft_strcmp(CURR_TOKEN, SEMICOLON)
		&& *CURR_TOKEN)
	{
		new_right_child(WORD, rdc, &rdc->tmp_node->left);
		if (get_next_token(rdc))
			cmd_suffix(rdc);
		return (1);
	}
	return (0);
}

int	cmd_prefix(t_rdc *rdc)
{
	if (io_redirect(rdc))
	{
		new_left_child(IO_REDIRECT, rdc, &rdc->tmp_node);
		if (get_next_token(rdc))
			cmd_prefix(rdc);
		return (1);
	}
	return (0);
}
