/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/10/23 15:14:40 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
# include <sys/wait.h>
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

typedef struct s_data
{
	struct s_cmd	*st_node;
	const char		*input;
	int				argc;
	char			**env;
	char			*cmd_path;
	int				origin_stdin;
	int				origin_stdout;
}t_data;

typedef enum s_obj
{
	PIPE,
	RED,
	EXECUTE,
	HEREDOC
}t_obj;

typedef struct s_cmd
{
	t_obj	type;
}t_cmd;

typedef struct s_exec
{
	t_obj		type;
	char		**argv;
}t_exec;

typedef struct s_pipe
{
	t_obj			type;
	t_cmd			*left;
	t_cmd			*right;
}t_pipe;

typedef struct s_red
{
	t_obj	type;
	int		mode;
	char	*file;
	int		fd;
	t_cmd	*cmd;
}t_red;

typedef struct s_here_d
{
	t_obj	type;
}t_hered;


//minishell.c
int			main(int ac, char **av, char **env);
void		fill_env(t_data *data, char **env);

//parsing/token_utils.c
void		make_token(t_token **token);
t_token		*find_last_token(t_token *t);

//parsing/free.c
void		free_tokens(t_token **t);

//execution/start_execution
void		start_exec(t_data *data);
void		exec_execu(t_exec *st_node, t_data *data, int need_child);
void		exec_pipe(t_pipe *st_node, t_data *data);
void		exec_red(t_red *st_node, t_data *data);
void		fill_test_struct(t_data *data); //Muss am ende rausgenommen werden, da befülltes struct von Parsing seite aus kommt

//execution/pipe
void		check_pipe(t_pipe *st_node, t_data *data, int last);
void		run_pipe(t_exec *st_node, t_data *data, int last);
void		child(t_exec *st_node, t_data *data, int last, int pipefd[2]);

//execution/help_execution
char		*find_path(t_data *data, t_exec *st_node);
void		free_dp(char **str);
char		**find_path_help(t_data *data);

#endif