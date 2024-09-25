/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/09/25 17:24:36 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"

// IDENTIFIER An identifier is things like a variable or a function name.
// They are referencing something.
// ASSIGNMENT An assignment just means that this is an operator that is used
// to assign a value. An operator is a symbol placed between
// identifiers or values to do something.
// O_PARANT is short for "opening parentheses." Parentheses are ( and ).
// C_PARANT is short for "closing parentheses."
enum e_flags
{
	BUILTIN = 2,
	IDENTIFIER,
	PLUS_ASSIGN,
	MINUS_ASSIGN,
	DIVI_ASSIGN,
	MULTI_ASSIGN,
	NUMBER,
	O_PARANT,
	C_PARANT,
	OTHER
};

typedef struct s_token
{
	char			*str;
	int				flag;
	int				id;

	struct s_token	*next;
	struct s_token	*next2;
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

typedef struct s_shell_elements
{
	t_obj			typ;
	t_command		command;
}t_shell_elements;

typedef enum s_obj
{
	PIPE,
	RED,
	EXECUTE,
	HEREDOC
}t_obj;

//parsing/token_utils.c
void		make_token(t_token **token);
t_token		*find_last_token(t_token *t);

//parsing/free.c
void		free_tokens(t_token **t);

//execution/start_execution
void		start_exec(void);
#endif