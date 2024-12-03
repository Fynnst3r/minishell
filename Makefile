NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = 	minishell.c\
		parsing/start_lexer.c parsing/lexer_utils.c\
		parsing/make_token.c\
		parsing/token_utils.c\
		parsing/expander.c parsing/expander_utils.c\
		parsing/evaluator.c\
		parsing/ast_files/make_ast2.c\
		error/error.c\
		garbage_collector/garbage_start.c\
		garbage_collector/ft_malloc.c\
		garbage_collector/free.c\
		exec/help_execution.c\
		exec/pipe.c\
		exec/start_execution.c\
		builtins/builtins1.c


# grep | sort | uniq

# int parse_1_command(token_list, *command)

# parse_tree(token_list) 
# {
# 	pipe
# 	parse_1_command(token_list, &pipe.left)
# 	if (token_list finished)
# 		pipe.type = EXECUTE
# 		return (...)
# 	while(not token_list end) {
# 		parse_1_command(token_list, &pipe.right)
# 		if (token_list not finished)
# 		{
# 			new_pipe.left = pipe
# 			pipe = new_pipe
# 		}
# 	}
# 	return (pipe)
# }

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