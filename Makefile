SRC =			main.c \
				utils/prompt.c \
				utils/get_next_line.c \
				utils/get_next_line_utils.c \
				lexer/lexer.c \
				lexer/is_operator.c \
				lexer/is_quote.c \
				lexer/is_builtin.c \
				lexer/join_char.c \
				lexer/token_recognition.c \
				token/create_token.c \
				token/destroy_token.c \
				token/add_new_token.c \
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

DIR_LIBFT =	./libs/libft
	

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

clean:			all
			make clean -C $(DIR_LIBFT)
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			all, clean, fclean, re, bonus
