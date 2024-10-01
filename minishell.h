/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/10/01 20:45:17 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_shell_elements	t_shell_elements;
// IDENTIFIER An identifier is things like a variable or a function name.
// They are referencing something.
// ASSIGNMENT An assignment just means that this is an operator that is used
// to assign a value. An operator is a symbol placed between
// identifiers or values to do something.
// O_PARANT is short for "opening parentheses." Parentheses are ( and ).
// C_PARANT is short for "closing parentheses."
enum e_flags
{
	WORD,
	NUMBER,
	O_PARANT,
	C_PARANT,
	SINGLE_QUOTE,
	T_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	OTHER
};

typedef struct s_token
{
	char			*str;
	enum e_flags	type;
	int				id;
	size_t			len;

	struct s_token	*next;
	struct s_token	*previous;
}			t_token;

typedef struct s_pipe
{
	t_shell_elements	*left_side;
	t_shell_elements	*right_side;
}t_pipe;

typedef struct s_red
{
	
}t_red;

typedef struct s_exe
{
	
}t_exe;

typedef struct s_here_doc
{
	
}t_heredoc;

typedef union s_command
{
	t_pipe		pipe;
	t_red		red;
	t_exe		exe;
	t_heredoc	heredoc;
}t_command;

typedef enum s_obj
{
	PIPE,
	RED,
	EXECUTE,
	HEREDOC
}t_obj;

typedef struct s_shell_elements
{
	t_obj			typ;
	t_command		command;
}t_shell_elements;

//parsing/token_utils.c
// void		make_token(t_token **token, char *str, int flag, int id);
int			ft_isspace(char c);
t_token		*make_token(void);
void		token_add_back(t_token **last, t_token *new);
t_token		*find_last_token(t_token *t);

//parsing/free.c
void		free_tokens(t_token **t);

//execution/start_execution
void		start_exec(void);
#endif