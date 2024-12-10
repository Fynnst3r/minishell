/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:37:28 by fforster          #+#    #+#             */
/*   Updated: 2024/12/04 15:16:39 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"
# include "lib/get_next_line/get_next_line.h"
# include <string.h>

extern int	g_signal;


typedef struct s_data
{
	struct s_cmd	*st_node;
	const char		*input;
	int				argc;
	char			**env;
	char			*cmd_path;
	int				origin_stdin;
	int				origin_stdout;
	// t_			*env_list;
}	t_data;

typedef struct s_vars
{
	char			*name;// Der Name der Umgebungsvariable (z. B. "PATH")
	char			*value;// Der Wert der Umgebungsvariable (z. B. "/usr/bin")
	struct s_vars	*next;
}	t_vars;

typedef enum s_obj
{
	PIPE,
	RED,
	EXECUTE,
	HEREDOC
}	t_obj;

typedef struct s_cmd
{
	t_obj	type;
}	t_cmd;

typedef struct s_exec
{
	t_obj		type;
	char		**argv;
}	t_exec;

typedef struct s_pipe
{
	t_obj			type;
	t_cmd			*left;
	t_cmd			*right;
}	t_pipe;

typedef struct s_red
{
	t_obj	type;
	int		mode;
	char	*file;
	int		fd;
	t_cmd	*cmd;
}	t_red;

typedef struct s_herd
{
	t_obj	type;
	t_cmd	*cmd;
	char	*del;
}	t_herd;


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
