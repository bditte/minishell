/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:45:14 by bditte            #+#    #+#             */
/*   Updated: 2021/04/15 11:46:38 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <wait.h>
# include <fcntl.h>

# define INPUT_EXIT	-1

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

/*
**	PARSING
*/

# define CURR_TOKEN	rdc->tokens[rdc->i]
# define LESS	"<"
# define GREAT	">"
# define DGREAT	">>"
# define PIPE	"|"
# define SEMICOLON	";"

# define SIMPLE_COMMAND			-5
# define PIPESEQUENCE			-4
# define COMPLETE_COMMAND		-3
# define CURR_ROOT				-2
# define TMP_NODE				-1
# define ROOT					0
# define WORD					1
# define IO_REDIRECT			2
# define CMD_PREFIX				3
# define CMD_NAME				4
# define CMD_WORD				5
# define CMD_ARGS				6

# define TYPE_LESS				10
# define TYPE_GREAT				11
# define TYPE_DGREAT			12
# define LEFT					13
# define RIGHT					14

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

/*
**	EXECUTOR
*/

typedef	struct	s_exec
{
	t_ast_node	curr_node;
	char		**envp;
	int			fdpipe[2];
	int			fdout;
	int			fdin;
	int			tmpin;
	int			tmpout;
	int			outfile;
	int			outype;
	int			infile;
	int			ret;
}				t_exec;


int			executor(t_ast_node *root, char **envp);
int			is_builtin(char *token);
int			exec_builtin(char *name, char **args);
char		**get_cmd_args(t_ast_node *node);
char		*add_path(char *cmd);
int			reset_fd(t_exec *exec);
int			init_fd(t_exec *exec, t_ast_node *node);
int			get_redirections(t_exec	*exec, t_ast_node *node);
int			check_redirections(t_ast_node *node, t_exec *exec);

/*
**	PARSER
*/

typedef	struct s_rdc
{
	char	**tokens;
	int			i;
	int			simple_i;
	int			is_last_token;
	int			nb_tokens;
	t_ast_node	*root;
	t_ast_node	*tmp_node;
	t_ast_node	*curr_root;
}				t_rdc;


int				parser(t_rdc *rdc, char ***tokens, int nb_tokens);
void			init_parser(t_rdc *rdc, int nb_tokens);
int				add_to_tmp(int type, t_rdc *rdc);
void			display_tree(t_ast_node *root);
void			update_tmp_node(int type, t_rdc *rdc);
void			new_left_node(int type, t_rdc *rdc, t_ast_node **p, t_ast_node **d);
void			new_right_node(int type, t_rdc *rdc, t_ast_node **p, t_ast_node **d);
void			new_right_child(int type, t_rdc *rdc, t_ast_node **p);
void			new_left_child(int type, t_rdc *rdc, t_ast_node **p);
t_ast_node		create_node(int type, t_rdc *rdc, t_ast_node *parent);
int				get_next_token(t_rdc *rdc);
void			assign_simple_command(t_rdc *rdc);
void			assign_complete_command(t_rdc *rdc);
int				cmd_prefix(t_rdc *rdc);
int				cmd_suffix(t_rdc *rdc);
int				cmd_name(t_rdc *rdc);
int				cmd_word(t_rdc *rdc);
int				io_redirect(t_rdc *rdc);

/*
**	LEXER
*/

# define BUF_SIZE	32


int				lexer(t_lexer *lexer);
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

void			add_new_token(t_lexer *l);

/*
**	BUILTINS
*/

int				bash_cd(char **av);
int				bash_echo(char **av);
int				bash_pwd(char **av);
int				bash_env(char **av, char **envp);
int				bash_exit(char **av);

/*
**	FREE
*/

void			free_lexer(t_lexer *lexer, int exit_code);
void			free_ast(t_rdc *root);
void			free_right_children(t_ast_node *node);
void			free_left_children(t_ast_node *node);
void			free_tab(char **args);

/*
**	ERROR
*/

void			print_error_and_exit(void);
void			builtin_error(char *str);
void			builtin_strerror(char *builtin);
int				print_errno(char *str);
/*
**	UTILS
*/

void			print_prompt(void);
int				ft_close(int fd);
#endif
