SRC =			main.c \
				utils/prompt.c \
				utils/get_next_line.c \
				utils/get_next_line_utils.c \
				utils/files.c \
				lexer/lexer.c \
				lexer/is_operator.c \
				lexer/is_quote.c \
				lexer/lexer_utils.c \
				lexer/token_recognition.c \
				parsing/parser.c \
				parsing/parse_args.c \
				parsing/parser_utils.c \
				parsing/ast.c \
				parsing/traverse_tree.c \
				executor/executor_utils.c \
				executor/executor.c \
				executor/handle_builtin.c \
				executor/get_cmd_args.c \
				executor/pipe.c \
				executor/redirection.c \
				executor/check_redirections.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/pwd.c \
				token/create_token.c \
				token/destroy_token.c \
				token/add_new_token.c \
				free/free_structures.c \
				free/free_ast.c \
				free/free_tab.c \
				free/free_ast_utils.c \
				error/error.c
					
NAME =			minishell

CC =			clang
	
FLAGS =			-Wall -Werror -Wextra			

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

OBJS =			$(SRCS:.c=.o)

RM =			rm -rf

HEADERS =	-I $(DIR_HEADERS)	\
				-I $(DIR_LIBFT)/include	\

DIR_HEADERS = 		./include/

DIR_SRCS =		./srcs/

DIR_OBJS = 		./objs/

DIR_LIBFT =		./libs/libft
	

LIBS = 	-L$(DIR_LIBFT) -lft	\

all:			$(NAME)

$(NAME) :		$(OBJS)
			@echo "Compiling Libft..."
			make -C $(DIR_LIBFT)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
				@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

bonus:

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
			make clean -C $(DIR_LIBFT)
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all, clean, fclean, re, bonus
