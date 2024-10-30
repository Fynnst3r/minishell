NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
SRC = src/minishell.c src/parsing/token_utils.c src/parsing/free.c src/exec/start_execution.c src/exec/help_execution.c src/exec/pipe.c src/builtins/builtins1.c
OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
LIBFT = lib/libft
GET_NEXT_LINE = lib/get_next_line

INLIBFT = -L $(LIBFT) -lft
INGET_NEXT_LINE = -L $(GET_NEXT_LINE) -lget_next_line

B := "\033[0;34m"
P := "\033[0;35m"
R := "\033[0;31m"
G := "\033[0;32m"
Y := "\033[0;33m"
DC := "\033[0;39m"

$(NAME): $(OBJS)
	@echo $(B)"Compiling libft..."$(DC)
	@cd $(LIBFT) && $(MAKE) --silent
	@cd $(GET_NEXT_LINE) && $(MAKE) --silent
	@echo $(G)"Compiling minishell..."$(DC)
	@cc $(OBJS) $(INLIBFT) $(IN_GETNEXTLINE) -o $(NAME) $(LDFLAGS)
	@echo $(Y)"Lets Go Minishell!!!"$(DC)

$(OBJ_DIR)/%.o: %.c | create_dirs
	@cc $(CFLAGS) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)/src $(OBJ_DIR)/src/parsing $(OBJ_DIR)/src/exec $(OBJ_DIR)/src/builtins

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@cd $(LIBFT) && $(MAKE) clean --silent
	@cd $(GET_NEXT_LINE) && $(MAKE) clean --silent

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@cd $(LIBFT) && $(MAKE) fclean --silent
	@cd $(GET_NEXT_LINE) && $(MAKE) fclean --silent
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re create_dirs


