NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRC = minishell.c src/parsing/token_utils.c src/parsing/free.c src/exec/start_execution.c
OBJS = $(SRC:.c=.o)
LIBFT = lib/libft

INLIBFT = -L $(LIBFT) -lft

B:= "\033[0;34m"
P:= "\033[0;35m"
R:= "\033[0;31m"
G:= "\033[0;32m"
Y:= "\033[0;33m"
DC:= "\033[0;39m"

$(NAME): $(OBJS)
	@echo $(B)"Compiling libft..."$(DC)
	@cd $(LIBFT) && $(MAKE) --silent
	@echo $(G)"minishell..."$(DC)
	@cc $(OBJS) $(INLIBFT) -o $(NAME)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@cd $(LIBFT) && $(MAKE) clean --silent

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFT) && $(MAKE) fclean --silent
	@echo $(Y)"\nEverything is properly cleaned!\n"$(DC)

re: fclean all

.PHONY: all clean fclean re
