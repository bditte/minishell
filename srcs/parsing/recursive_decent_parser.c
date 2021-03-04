/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_decent_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:47:16 by bditte            #+#    #+#             */
/*   Updated: 2021/03/03 16:38:31 by bditte           ###   ########.fr       */
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

int cmd_prefix(t_rdc *rdc)
{
    
}

int simple_command(t_rdc *rdc)
{
    if (cmd_prefix)
    {
        while (is_cmd_prefix)
        {
            cmd_prefix();
            next_token;
        }
        cmd_word();
    }
    else
    {
        if (!cmd_name)
            return (0);
    }
    cmd_suffix();
}

int pipesequence(t_rdc *rdc)
{
    simple_command(rdc);
    accept(rdc->tokens[rdc->i], "|");
}

int complete_commands(t_rdc *rdc)
{
    pipesequence(rdc);
    accept(rdc->tokens[rdc->i], ";");
}

int parser(char ***tokens)
{
    t_rdc   *rdc;

    rdc->i = 0;
    rdc->tokens = *tokens;
    complete_commands(rdc);
}