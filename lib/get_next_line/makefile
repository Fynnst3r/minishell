NAME = libget_next_line.a
CFLAGS = -Wall -Werror -Wextra
CC = cc
MAIN = get_next_line.c get_next_line_utils.c

mains = $(MAIN:.c=.o)

$(NAME): $(mains)
	@ar -rs $(NAME) $^ > /dev/null 2>&1

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -f *.o

all: $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
