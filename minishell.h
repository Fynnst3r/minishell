/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/12/10 19:19:03 by fforster         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

// OWN LIBS
# include "libft/libft.h"
# include "src/garbage_collector/garbage_collector.h"
// COLOR
# include "src/parsing/colors.h"

extern int	g_signal;

enum e_flags
{
	WORD = 0,
	T_PIPE = 1,
	T_OUT = 2,
	T_APP = 3,
	T_IN = 4,
	T_HERE = 5,
	T_SKIP = 6,
	PATH = 7
};

typedef struct s_data
{
	struct s_cmd	*st_node;
	char			*input;
	int				argc;
	char			**env;
	char			*cmd_path;
	int				exit_status;
	int				origin_stdin;
	int				origin_stdout;
	t_list			*env_list;
}						t_data;

typedef struct s_lexer
{
	char		*str;
	size_t		position;
	size_t		read;
	char		last_c;
	char		curr_c;
	bool		keepempty;
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

typedef struct s_env_entry
{
	char	*name;
	char	*value;
}	t_env_entry;

typedef enum s_obj
{
	PIPE = 0,
	RED = 1,
	EXECUTE = 2,
	HEREDOC = 3
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
}					t_herd;

/******************************************************************************/
//<<<<<<<<<<<<<<<<<<<<   fforsters parsing functions   >>>>>>>>>>>>>>>>>>>>>>>//
/******************************************************************************/
//minishell.c
// void		fill_env(t_data *data, char **env);

//parsing/new_lex.c
int			start_lexer(char *input, t_data *data);
int			get_str(t_lexer *lex, t_token **tofill);
//parsing/new_lex_utils.c
t_lexer		init_lex(char *input);
int			is_special_char(char c);
int			ft_isspace(char c);
int			skip_quote(const char *s, size_t *i);
int			handle_special(char *input, t_lexer *lex, t_token **toktop,
				size_t start);

//parsing/make_token.c
int			make_token(t_token **tok, t_lexer *lexer);
void		make_special_token(t_token **toktop, char *str, int e_flag);

//parsing/token_utils.c
void		print_token_data(t_token *top);
void		remove_token(t_token *to_del);
t_token		*find_last_token(t_token *t);
t_token		*find_id(t_token *t, int find);
void		set_token_id(t_token *t);
void		set_token_types(t_token *t);

// parsing/expander.c
void		expand_tokens(t_token **toktop, int exit_status, t_lexer l);
char		*check_val(char *s, t_lexer *l);
char		*ft_strjoin_at(char *s1, char *s2, t_lexer *l, bool print_exit);
char		*add_char(char *ret, char add, size_t *position);
//..uitls.c
char		*keep_expanding(char *s, char *ret, t_lexer *l, char *exit_status);
char		*stop_expanding(char *s, char *ret, t_lexer *l);

//evaluator.c
int			evaluator(t_token *toktop);

///parsing/ast_files/make_ast2.c
void		make_ast2(t_data *data, t_token **toktop);
int			scan_cmd_type(t_token *t);
void		print_exec(t_exec *cmd);
void		print_pipe_ast(t_pipe *pipe);
t_exec		*make_cmd_node(t_token *t);
t_red		*make_red_node(t_token *t);
t_herd		*make_herd_node(t_token *t);
///parsing/ast_files/make_pipe_ast.c
t_pipe		*make_pipe_ast(t_token **toktop);

//error/error.c
void		ft_error(char *message, int errcode, t_token **toktop);
//garbage_collector/free.c
void		free_tokens(t_token **t);

/******************************************************************************/
//<<<<<<<<<<<<<<<<<<<<<    ymauk execution functions    >>>>>>>>>>>>>>>>>>>>>>//
/******************************************************************************/

//minishell.c
int			main(int ac, char **av, char **env);
void		setting_data(t_data *data);

//execution/start_execution
void		start_exec(t_data *data, t_cmd *cmd);
void		exec_execu(t_exec *st_node, t_data *data);
void		exec_pipe(t_pipe *st_node, t_data *data);
void		exec_red(t_red *st_node, t_data *data);
void		exec_heredoc(t_herd *st_node, t_data *data);
void		fill_test_struct(t_data *data); //Muss am ende rausgenommen werden, da befülltes struct von Parsing seite aus kommt

//execution/pipe
void		check_pipe(t_pipe *st_node, t_data *data, int last);
void		run_pipe(t_cmd *st_node, t_data *data, int last);
void		child(t_cmd *st_node, t_data *data, int last, int pipefd[2]);

//execution/help_execution
char		*find_path(t_data *data, t_exec *st_node);
void		free_dp(char **str);
char		**find_path_help(t_data *data);
int			write_in_file(int fd, t_herd *st_node);

//execution/exec_utils
void		fill_env(t_data *data, char **env);
void		fill_env_list(t_data *data, char **env);
// void		ft_add_node_back(t_node **list, t_node *new_node);
// t_node		*create_node(const char *env_entry);
// void		print_env_list(t_node *list);

//builtins/builtins1
int			check_builtins(t_data *data, char **cmd);
void		exec_echo(char **cmd);

// void	exec_cd(char **cmd);
void		exec_pwd(t_data *data);
void		exec_env(t_data *data);
// void		exec_exit(char **cmd);
void		exec_unset(t_data *data, char **cmd);
#endif