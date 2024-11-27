/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/11/27 17:18:22 by fforster         ###   ########.fr       */
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
// COLOR
# include "parsing/colors.h"

enum e_flags
{
	WORD,
	SINGLE_Q,
	DOUBLE_Q,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APP,
	T_HERE,
	PATH
};

typedef struct s_lexer
{
	char		*str;
	size_t		position;
	size_t		read;
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

/*
	am ende immer commands
	links von pipes sind command nodes
	rechts  koennen entweder eine pipe oder ein command sein
	commands left/right sind immer NULL
	eine pipe hat immer left/right

	-fuer execcution: started bei root node und geht immer wenn moeglich links
	-leaf nodes sind immer commands
	-nach dem execution einens commands zur parent node return und nach rechts gehen
		dann wieder nach links soweit es geht
		(es sei denn es gibt kein links, dann ist es ein command)

					Node(PIPE)
			/						\
	node(command 1):					Node(PIPE)
	-liste von redirs				/				\
	-name/path						Node(command 2)	Node(pipe)
	-argv										/				\			
											node(command 3)		node(command 4)
*/

//type um 'data' in t_node auf anderes struct zu casten
// yannisdata
typedef struct s_data
{
	struct s_cmd	*st_node;
	char			*input;
	int				argc;
	char			**env;
	char			*cmd_path;
	int				origin_stdin;
	int				origin_stdout;
}						t_data;
// yannisdata
typedef enum s_type
{
	PIPE,
	COMMAND,
	OTHER
}	t_type;
typedef struct s_ast	t_ast;

typedef struct s_ast
{
	t_type	type;
	t_ast	*left;
	t_ast	*right;
	void	*data;//pointer zu t_pipe oder t_command struct
}	t_ast;

typedef enum e_redirtype
{
	// T_CREATE,// efg. SHELL: > filename		makes a new file and asks for a string to put in to file.
	T_REDIN = 4,
	T_REDOUT = 5,
	T_APPEND = 6,
	T_HEREDOC = 7
}	t_redirtype;

typedef struct s_redir 	t_redir;
/*
	linked list von redirs:
	delimeter fuer alle redirs bis auf T_HEREDOC ist das NULL
*/
typedef struct s_redir
{
	t_redirtype	type;
	char		*file;
	char		*delimeter;
	t_redir		*next;
}	t_redir;

typedef struct s_pipe
{
	
}	t_pipe;

typedef struct s_command
{
	t_redir		*redirs;//linked list
	char		*name;//str
	char		**argv;//str array
	//char		**env;
}	t_command;


// <<<<<<<<<<<<<<<<<<<<<<<<<FUNCTIONS>>>>>>>>>>>>>>>>>>>>>>>>>
//minishell.c
// void		fill_env(t_data *data, char **env);

//parsing/new_lex.c
t_ast		*start_lexer(char *input);
char		*get_str(t_lexer *lex);
t_lexer		init_lex(char *input);

//parsing/new_lex_utils.c
int			is_special_char(char c);
int			ft_isspace(char c);
bool		isemptystring(const char *s);
void		skip_quote(const char *s, size_t *i);
int			handle_special(char *input, t_lexer *lex, t_token **toktop,
				size_t start);

//parsing/token_utils.c
void		print_token_data(t_token *top);
t_token		*find_id(t_token *t, int find);
void		set_token_id(t_token *t);
void		set_token_types(t_token *t);
t_token		*find_last_token(t_token *t);
void		make_token(t_token **tok, t_lexer *lexer);
void		make_special_token(t_token **toktop, char *str, int e_flag);

//parsing/expander.c
void		expand_tokens(t_token **toktop);
char		*check_val(char *s, t_lexer *l);
char		*ft_strjoin_at(char *s1, char *s2, t_lexer *l);
//make_ast.c
t_ast		*make_ast(t_token **toktop);
//parsing/free.c
void		free_tokens(t_token **t);//??????
// yannis.h ///////////////////////////////////////////////////////////////////////////////////
// typedef struct s_data
// {
// 	struct s_cmd	*st_node;
// 	char		*input;
// 	int				argc;
// 	char			**env;
// 	char			*cmd_path;
// 	int				origin_stdin;
// 	int				origin_stdout;
// }						t_data;

// typedef enum s_obj
// {
// 	PIPE,
// 	RED,
// 	EXECUTE,
// 	HEREDOC
// }					t_obj;

// typedef struct s_cmd
// {
// 	t_obj		type;
// }					t_cmd;

// typedef struct s_exec
// {
// 	t_obj		type;
// 	char		**argv;
// }					t_exec;

// typedef struct s_pipe
// {
// 	t_obj		type;
// 	t_cmd		*left;
// 	t_cmd		*right;
// }					t_pipe;

// typedef struct s_red
// {
// 	t_obj		type;
// 	int			mode;
// 	char		*file;
// 	int			fd;
// 	t_cmd		*cmd;
// }					t_red;

// typedef struct s_here_d
// {
// 	t_obj		type;
// 	t_cmd		*cmd;
// 	char		*del;
// }					t_hered;

// //execution/start_execution
// void		start_exec(t_data *data);
// void		exec_execu(t_exec *st_node, t_data *data);
// void		exec_pipe(t_pipe *st_node, t_data *data);
// void		fill_test_struct(t_data *data); //Muss am ende rausgenommen werden, da befülltes struct von Parsing seite aus kommt

// //execution/help_execution
// char		*find_path(t_data *data, t_exec *st_node);
// void		free_dp(char **str);

// //execution/pipe
// void		pipe_left(t_exec *st_node_left, int pipefd[2], t_data *data);
// void		pipe_right(t_exec *st_node_right, int pipefd[2], t_data *data);
#endif
