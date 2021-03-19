/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:14 by bditte            #+#    #+#             */
/*   Updated: 2021/03/19 16:42:24 by bditte           ###   ########.fr       */
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

typedef	struct s_mini_parser
{
	int		curr_tkn;
	int		first_tkn;
	int		nb_tkns;
	int		tkn_type;
}				t_mini_parser;


typedef struct s_cmd
{
	int				nb_cmds;
	int				curr_cmd;
	int				first_tkn;
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
	int		i;
}				t_lexer;


typedef struct s_token
{
	char	*value;
	int		type;
}				t_token;

/*
**	PARSING
*/

# define CURR_TOKEN	rdc->tokens[rdc->i]
# define LESS	"<"
# define GREAT	">"
# define DGREAT	">>"
# define PIPE	"|"
# define SEMICOLON	";"

# define TMP_NODE				-1
# define ROOT					0
# define WORD					1
# define IO_REDIRECT			2
# define CMD_PREFIX				3
# define CMD_NAME				4
# define CMD_WORD				5
# define CMD_ARGS				6
# define SIMPLE_COMMAND			7
# define TYPE_LESS				10
# define TYPE_GREAT				11
# define TYPE_DGREAT			12

typedef	struct	s_ast_node
{
	int						type;
	int						sub_type;
	char					*data;
	int						value;
	struct s_ast_node		*parent;
	struct s_ast_node		*left;
	struct s_ast_node		*right;
}				t_ast_node;

typedef	struct s_rdc
{
	char	**tokens;
	int			i;
	int			simple_i;
	int			is_last_token;
	int			nb_tokens;
	t_ast_node	*root;
	t_ast_node	*tmp_node;
}				t_rdc;

typedef	struct	s_node_info
{
	int			type;
	
}				t_node_info;


typedef struct s_parser
{
	t_cmd	**cmds;
	int		nb_cmds;
	int		curr_cmd;
	int		first_tkn;
}				t_parser;

int				parser(t_rdc *rdc, char ***tokens, int nb_tokens);
void			init_parser(t_rdc *rdc, int nb_tokens);
int				add_to_tmp(int type, t_rdc *rdc);
void			display_tree(t_ast_node *root);
void			update_tmp_node(int type, t_rdc *rdc);
void			new_node(int type, t_rdc *rdc, t_ast_node **parent, t_ast_node **dest);

t_ast_node	create_node(int type, t_rdc *rdc, t_ast_node *parent);
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

/*
**	BUILTINS
*/

int				bash_cd(char **av);
int				bash_echo(char **av);
int				bash_pwd(char **av);
int				bash_env(char **av, char **envp);

/*
**	FREE
*/

void			free_parser(t_rdc *rdc);
void			free_lexer(t_lexer *lexer, int exit_code);
void			free_ast(t_ast_node *root);

/*
**	ERROR
*/

void			print_error_and_exit(void);

/*
**	UTILS
*/

void			print_prompt(void);

#endif
