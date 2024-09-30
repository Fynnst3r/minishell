NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror -lreadline 

SRCS = 	minishell.c\
		token_utils.c\
		free.c\
		new_split.c

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