/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:28:05 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 14:14:00 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_nb_args(t_ast_node *node, int *nb_args)
{
	*nb_args = 1;
	node = node->right;
	while (node)
	{
		if (node->type != IO_REDIRECT)
			(*nb_args)++;
		node = node->right;
	}
}

char	**get_cmd_args(t_ast_node *node)
{
	int		nb_args;
	char	**args;

	get_nb_args(node, &nb_args);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		print_error_and_exit();
	args[0] = ft_strdup(node->data);
	args[nb_args] = 0;
	node = node->right;
	args++;
	while (nb_args > 1 && node)
	{
		if (node->type != IO_REDIRECT)
			*args++ = ft_strdup(node->data);
		node = node->right;
	}
	args -= nb_args;
	return (args);
}