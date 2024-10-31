NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -lreadline 

SRCS = 	minishell.c\
		parsing/token_utils.c\
		parsing/lexer.c\
		parsing/new_split.c\
		parsing/new_split_utils.c\
		parsing/process_split.c\
		garbage_collector/garbage_start.c\
		garbage_collector/ft_malloc.c\
		garbage_collector/free.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all