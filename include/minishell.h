/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:14 by bditte            #+#    #+#             */
/*   Updated: 2021/02/15 12:19:29 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <errno.h>
# define INPUT_EXIT	-1

typedef struct s_simple_cmd
{
	int			nb_args;
	int			nb_available_args;
	char		**args;
}				t_simple_cmd;

typedef struct s_cmd
{
	int				nb_cmds;
	int				nb_available_cmds;
	int				outfile;
	int				infile;
	int				errfile;
	t_simple_cmd	**simple_cmds;
}				t_cmd;

typedef struct s_lexer
{
	char	**tokens;
	char	*buffer;
	char	*line;
	int		position;
	int		buffsize;
	int		quoted;
	int		nb_tokens;
	int		current_token;
}				t_lexer;


typedef struct s_token
{
	char	*value;
	int		type;
}				t_token;

/*
**	PARSING
*/

typedef struct s_parser
{
	t_cmd	**cmds;
	int		nb_cmds;
	
}				t_parser;

int				parsing(t_lexer *l, t_parser *p);
int				insert_cmd(t_cmd *cmd, t_simple_cmd *s_cmd);
int				insert_arg(t_simple_cmd *cmd, char *arg);

/*
**	LEXER
*/

# define BUF_SIZE	32


int				lexer(t_lexer *lexer);
int				is_builtin(char *token, char next_char);
int				is_operator(char *token, char next_char);
int				is_first_operator(char c);
int				ft_isquote(int c);
int				token_recognition(t_lexer *l, char next_char);
void			reset_lexer_struct(t_lexer *lexer);
void			join_char(t_lexer *lexer, char c);
void			get_nb_tokens(t_lexer *lexer, char *line);
void			reset_lexer_struct(t_lexer *lexer);
void			init_lexer_struct(t_lexer *lexer);

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

void			print_error_and_exit(void);

/*
**	UTILS
*/

void			print_prompt(void);

#endif
