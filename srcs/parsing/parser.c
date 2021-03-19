/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:47:16 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:48:06 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int accept(char *curr_tkn, char *symbol)
{
    if (!ft_strcmp(curr_tkn, symbol))
    {
        return (1);
    }
    return (0);
}

int expect(char *curr_tkn, char *symbol)
{
    if (accept(curr_tkn, symbol))
        return (1);
    return (0);
}

int	get_next_token(t_rdc *rdc)
{
	if (!rdc->tokens[rdc->i + 1])
	{
		rdc->is_last_token = 1;
		return (0);
	}
	rdc->i++;
	rdc->simple_i++;
	return (1);
	
}

int	filename(t_rdc *rdc)
{
	(void)rdc;
	return (1);
}

int io_redirect(t_rdc *rdc)
{
	if (!ft_strcmp(CURR_TOKEN, LESS) || !ft_strcmp(CURR_TOKEN, GREAT)
		|| !ft_strcmp(CURR_TOKEN, DGREAT))
	{
		if (!get_next_token(rdc))
			return (0);
		if (filename(rdc))	//check rule 2
			return (1);
	}
	return (0);
}

int	cmd_word(t_rdc *rdc)
{
	//ajouter handle = 
	//create_token(tkn, WORD);
	(void)rdc;
	if (ft_strcmp(CURR_TOKEN, PIPE) && ft_strcmp(CURR_TOKEN, SEMICOLON)
		&& *CURR_TOKEN)
	{
		printf("%d IS CMD_WORD \n", rdc->i);
		return (1);
	}
	return (0);
}

int	cmd_name(t_rdc *rdc)
{
	//ajouter handle =
	if (rdc->simple_i == 0)
	{
		printf("%d IS CMD_NAME \n", rdc->i);
		//create_token(tkn, WORD);
		return (1);
	}
	return (0);
}

int	cmd_suffix(t_rdc *rdc)
{
	printf("curr_token %s\n", CURR_TOKEN);
	if (io_redirect(rdc))
	{
		printf("%d IS IO_REDIRECT \n", rdc->i);
		//create_io_node();
		//new_node(IO_REDIRECT, rdc, rdc->tmp_node->left->right);
		if (get_next_token(rdc))
			cmd_suffix(rdc);
		printf("succccess\n");
		return (1);
	}
	if (ft_strcmp(CURR_TOKEN, PIPE) && ft_strcmp(CURR_TOKEN, SEMICOLON)
		&& *CURR_TOKEN)
	{
		printf("%d IS CMD_ARG \n", rdc->i);
		//add_tkn_to_cmd_args();
		if (get_next_token(rdc))
			cmd_suffix(rdc);
		return (1);
	}
	return (0);
}

int cmd_prefix(t_rdc *rdc)
{
	if (io_redirect(rdc))
	{
		printf("%d PREFIX IS IO_REDIRECT \n", rdc->i);
		new_node(IO_REDIRECT, rdc, &rdc->root, &rdc->root->left);
		if (get_next_token(rdc))
			cmd_prefix(rdc);
		return (1);
		
	}
	printf("IS NOT IO_REDIRECT \n");
	return (0);	
}

int simple_command(t_rdc *rdc)
{
	rdc->simple_i = 0;
    if (cmd_prefix(rdc))
    {
		if (!rdc->is_last_token)
        {
			if (cmd_word(rdc))
			{
				new_node(CMD_WORD, rdc, &rdc->root, &rdc->root->left);
				//printf("TMP NODE DATA %s\n", rdc->tmp_node->data);
				get_next_token(rdc);
				display_tree(rdc->root);
			}
		}	
    }
    else
    {
        if (cmd_name(rdc))
        {
			//add_to_tmp(CMD_NAME, rdc);
			get_next_token(rdc);
			display_tree(rdc->root);
		}
    }
    if (!rdc->is_last_token)
		cmd_suffix(rdc);
	printf("END OF SUFFIX\n");
	return (1);
}

int pipesequence(t_rdc *rdc)
{
    if (simple_command(rdc))
	{
		printf("IS SIMPLE_COMMAND \n");
		//create simple_command node
		if (!ft_strcmp(CURR_TOKEN, "|"))
		{
			//create pipe node
			printf("PIPE NODE \n");
			if (get_next_token(rdc))
				pipesequence(rdc);
			return (1);
		}
		return (1);
	}
	printf("IS NOT SIMPLE_COMMAND \n");
	return (0);
}

int complete_commands(t_rdc *rdc)
{
    if (pipesequence(rdc))
	{
		printf("IS PIPESEQUENCE \n");
		//create pipesequence node
		if (!ft_strcmp(CURR_TOKEN, ";"))
		{
			if (get_next_token(rdc))
				pipesequence(rdc);
			return (1);
		}
		return (1);		
	}
	printf("IS NOT PIPESEQUENCE \n");
	return (0);
}

int parser(t_rdc *rdc, char ***tokens, int nb_tokens)
{
//	t_ast_node	node;
	init_parser(rdc, nb_tokens);
	printf("RDC INIT DONE\n");
	rdc->tokens = *tokens;
	complete_commands(rdc);
	printf("END OF PARSER\n");
	return (0);
}