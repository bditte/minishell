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

int rd_parser(char **tokens)
{

}