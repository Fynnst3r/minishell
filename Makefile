NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -lreadline -g -fsanitize=address
SRCS = src/minishell.c \
		src/parsing/start_lexer.c src/parsing/lexer_utils.c \
		src/parsing/make_token.c \
		src/parsing/token_utils.c \
		src/parsing/expander.c src/parsing/expander_utils.c \
		src/parsing/evaluator.c \
		src/parsing/ast_files/make_ast2.c \
		src/parsing/ast_files/pipe_ast.c \
		src/error/error.c \
		src/error/errno_print.c \
		src/garbage_collector/garbage_start.c \
		src/garbage_collector/ft_malloc.c \
		src/garbage_collector/free.c \
		src/exec/start_execution.c \
		src/exec/help_execution.c \
		src/exec/exec_utils.c \
		src/exec/pipe.c \
		src/builtins/builtins1.c \
		src/builtins/echo.c \
		src/builtins/export.c \
		src/builtins/unset.c\
		src/builtins/cd.c

OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBFT = libft
INLIBFT = -L $(LIBFT) -lft

B := "\033[0;34m"
G := "\033[0;32m"
Y := "\033[0;33m"
DC := "\033[0;39m"

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(B)"Compiling libft..."$(DC)
	@cd $(LIBFT) && $(MAKE) --silent
	@echo $(G)"Compiling minishell..."$(DC)
	@cc $(OBJS) $(INLIBFT) -o $(NAME) $(LDFLAGS)
	@echo $(Y)"Lets Go Minishell!!!"$(DC)

$(OBJ_DIR)/%.o: %.c | create_dirs
	@cc $(CFLAGS) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)/src \
		$(OBJ_DIR)/src/parsing \
		$(OBJ_DIR)/src/parsing/ast_files \
		$(OBJ_DIR)/src/error \
		$(OBJ_DIR)/src/garbage_collector \
		$(OBJ_DIR)/src/exec \
		$(OBJ_DIR)/src/builtins

clean:
	@rm -f $(OBJS)
	@cd $(LIBFT) && $(MAKE) clean --silent

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFT) && $(MAKE) fclean --silent
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re create_dirs