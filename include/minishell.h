/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:14 by bditte            #+#    #+#             */
/*   Updated: 2021/02/12 17:08:32 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>

#define INPUT_EXIT	-1

typedef	struct	s_simple_cmd
{
	int			nb_of_tokens;
	int			outfile;
	int			infile;
	int			errfile;
	char		**tokens;
}				t_simple_cmd;

typedef	struct	s_cmds
{
	int				nb_of_cmds;
	t_simple_cmd	cmds;
}				t_cmds;

typedef	struct	s_token
{
	char	*value;
	int		type;
}				t_token;

/*
**	LEXER
*/

#define BUF_SIZE	32

typedef	struct s_lexer
{
	t_list	*tokens_lst;
	char	**tokens;
	char	*buffer;
	int		position;
	int		buffsize;
	int		quoted;
	int		nb_tokens;
	int		current_token;
}				t_lexer;

int				lexer(t_lexer *lexer);
int				is_builtin(char *token, char next_char);
int				is_operator(char *token, char next_char);
int				is_first_operator(char c);
int				ft_isquote(int c);
int				token_recognition(t_lexer *l, char next_char);
/*
**	TOKEN
*/

t_token			create_token(char *value, int type);
void			destroy_token(t_token token);
void			add_new_token(t_lexer *l);

# define WORD	1
# define ASSIGNEMENT_WORD	2
# define NAME		3
# define IO_NUMBER	4
# define GREAT		5
# define DGREAT		6
# define LESS		7

/*
**	ERROR
*/

void			print_error_and_exit();

/*
**	UTILS
*/

void			print_prompt();

#endif
