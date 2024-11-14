/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/11/14 19:00:21 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
// OWN LIBS
# include "libft/libft.h"
# include "garbage_collector/garbage_collector.h"

enum e_flags
{
	WORD,
	SINGLE_Q,
	DOUBLE_Q,
	T_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	OTHER
};

typedef struct s_lexer
{
	char		*str;
	size_t		position;
	size_t		read_cursor;
	char		last_c;
	char		curr_c;
}					t_lexer;

typedef struct s_token
{
	char			*str;
	int				type;
	int				id;
	size_t			len;

	struct s_token	*next;
	struct s_token	*previous;
}						t_token;

typedef struct s_data
{
	struct s_cmd	*st_node;
	const char		*input;
	int				argc;
	char			**env;
	char			*cmd_path;
	int				origin_stdin;
	int				origin_stdout;
}						t_data;

typedef enum s_obj
{
	PIPE,
	RED,
	EXECUTE,
	HEREDOC
}					t_obj;

typedef struct s_cmd
{
	t_obj		type;
}					t_cmd;

typedef struct s_exec
{
	t_obj		type;
	char		**argv;
}					t_exec;

typedef struct s_pipe
{
	t_obj		type;
	t_cmd		*left;
	t_cmd		*right;
}					t_pipe;

typedef struct s_red
{
	t_obj		type;
	int			mode;
	char		*file;
	int			fd;
	t_cmd		*cmd;
}					t_red;

typedef struct s_here_d
{
	t_obj		type;
	t_cmd		*cmd;
	char		*del;
}					t_hered;

//minishell.c
void		fill_env(t_data *data, char **env);

//parsing/new_lex.c
void		start_lexer(char *input);
char		*get_str(t_lexer *lex);

//parsing/new_lex_utils.c
int			is_special_char(char c);
int			ft_isspace(char c);
bool		isemptystring(const char *s);
void		skip_quote(const char *s, size_t *i);

//parsing/token_utils.c
void		make_token(t_token **tok, t_lexer *lexer);
t_token		*find_last_token(t_token *t);
void		print_token_data(t_token *top);

//parsing/free.c
void		free_tokens(t_token **t);

//execution/start_execution
void		start_exec(t_data *data);
void		exec_execu(t_exec *st_node, t_data *data);
void		exec_pipe(t_pipe *st_node, t_data *data);
void		fill_test_struct(t_data *data); //Muss am ende rausgenommen werden, da befülltes struct von Parsing seite aus kommt

//execution/help_execution
char		*find_path(t_data *data, t_exec *st_node);
void		free_dp(char **str);

//execution/pipe
void		pipe_left(t_exec *st_node_left, int pipefd[2], t_data *data);
void		pipe_right(t_exec *st_node_right, int pipefd[2], t_data *data);
#endif