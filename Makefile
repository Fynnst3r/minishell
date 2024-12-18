NAME = minishell

CC = cc

# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	src/minishell.c\
		src/parsing/start_lexer.c src/parsing/lexer_utils.c\
		src/parsing/make_token.c\
		src/parsing/token_utils.c\
		src/parsing/expander.c src/parsing/expander_utils.c\
		src/parsing/evaluator.c\
		src/parsing/ast_files/make_ast2.c\
		src/parsing/ast_files/pipe_ast.c\
		src/error/error.c\
		src/garbage_collector/garbage_start.c\
		src/garbage_collector/ft_malloc.c\
		src/garbage_collector/free.c\
		src/exec/start_execution.c\
		src/exec/help_execution.c\
		src/exec/exec_utils.c\
		src/exec/pipe.c\
		src/builtins/builtins1.c\
		src/builtins/export.c\
		src/builtins/unset.c



OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	cc $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all