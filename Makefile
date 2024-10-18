NAME = minishell
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
SRC = src/minishell.c src/parsing/token_utils.c src/parsing/free.c src/exec/start_execution.c src/exec/help_execution.c src/exec/pipe.c
OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
LIBFT = lib/libft

INLIBFT = -L $(LIBFT) -lft

B := "\033[0;34m"
P := "\033[0;35m"
R := "\033[0;31m"
G := "\033[0;32m"
Y := "\033[0;33m"
DC := "\033[0;39m"

$(NAME): $(OBJS)
	@echo $(B)"Compiling libft..."$(DC)
	@cd $(LIBFT) && $(MAKE) --silent
	@echo $(G)"Compiling minishell..."$(DC)
	@cc $(OBJS) $(INLIBFT) -o $(NAME) $(LDFLAGS)
	@echo $(Y)"Lets Go Minishell!!!"$(DC)

$(OBJ_DIR)/%.o: %.c | create_dirs
	@cc $(CFLAGS) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)/src $(OBJ_DIR)/src/parsing $(OBJ_DIR)/src/exec

all: $(NAME)

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


