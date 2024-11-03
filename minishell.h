/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/11/03 18:13:48 by fforster         ###   ########.fr       */
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
	O_PARANT,
	C_PARANT,
	SINGLE_Q,
	DOUBLE_Q,
	T_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	OTHER
};

typedef struct s_token
{
	char			*str;
	int				type;
	int				id;
	size_t			len;

	struct s_token	*next;
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
	t_obj	type;
	t_cmd	*left;
	t_cmd	*right;
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
	t_cmd	*cmd;
	char	*del;
}t_hered;

//minishell.c
// int			main(int ac, char **av, char **env);
void		fill_env(t_data *data, char **env);

//parsing/token_utils.c
// void		make_token(t_token **token, char *str, int flag, int id);
int			ft_isspace(char c);
void		print_token_data(t_token *top);
t_token		*make_token(void);
void		token_add_back(t_token **last, t_token *new);
t_token		*find_last_token(t_token *t);

//parsing/free.c
void		free_tokens(t_token **t);
char		**new_split(char const *s);

//parsing/lexer.c
void		start_lexer(char *input);

//parsing/newsplit.c
void		f_free_split_strs(char **split);
int			is_special_char(char c);
//parsing/newsplit_utils.c
// int			catch_dollar_num(char *s);
// char		*ft_strndup(char *s, size_t n);
// char		*found_dollar_sign(char *s, size_t k);
// char		*ft_strjoin_at(char *s1, char *s2, size_t start);

//parsing/proccess_split.c
int			process_split(char **split);
char		*get_env_value(char *str, size_t l);
int			quote_status(char c, int ignore);
int			is_special_char(char c);
bool		isemptystring(const char *s);
void		skip_quote(const char *s, size_t *i, size_t *count);

// 
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