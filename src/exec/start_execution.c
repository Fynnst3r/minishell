/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/11 17:32:10 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_test_struct(t_data *data)
{
	t_exec *exec_ls = malloc(sizeof(t_exec));
    exec_ls->type = EXECUTE;
    exec_ls->argv = malloc(3 * sizeof(char *));
    exec_ls->argv[0] = strdup("ls");
    exec_ls->argv[1] = strdup("-l");
    exec_ls->argv[2] = NULL;

	t_exec *exec_grep = malloc(sizeof(t_exec));
    exec_grep->type = EXECUTE;
    exec_grep->argv = malloc(3 * sizeof(char *));
    exec_grep->argv[0] = strdup("grep");
    exec_grep->argv[1] = strdup("txt");
    exec_grep->argv[2] = NULL;

	t_exec *exec_sort = malloc(sizeof(t_exec));
    exec_sort->type = EXECUTE;
    exec_sort->argv = malloc(2 * sizeof(char *));
    exec_sort->argv[0] = strdup("sort");
    exec_sort->argv[1] = NULL;

	t_exec *exec_wc = malloc(sizeof(t_exec));
    exec_wc->type = EXECUTE;
    exec_wc->argv = malloc(3 * sizeof(char *));
    exec_wc->argv[0] = strdup("wc");
    exec_wc->argv[1] = strdup("-l");
    exec_wc->argv[2] = NULL;

	// 5. Erstellen der Pipe für 'ls -l | grep txt'
    t_pipe *pipe_ls_grep = malloc(sizeof(t_pipe));
    pipe_ls_grep->type = PIPE;
    pipe_ls_grep->left = (struct t_shell *)exec_ls;
    pipe_ls_grep->right = (struct t_shell *)exec_grep;

    // 6. Erstellen der Pipe für '(ls -l | grep txt) | sort'
    t_pipe *pipe_grep_sort = malloc(sizeof(t_pipe));
    pipe_grep_sort->type = PIPE;
    pipe_grep_sort->left = (struct t_shell *)pipe_ls_grep;
    pipe_grep_sort->right = (struct t_shell *)exec_sort;

    // 7. Erstellen der Pipe für '((ls -l | grep txt) | sort) | wc -l'
    t_pipe *pipe_sort_wc = malloc(sizeof(t_pipe));
    pipe_sort_wc->type = PIPE;
    pipe_sort_wc->left = (struct t_shell *)pipe_grep_sort;
    pipe_sort_wc->right = (struct t_shell *)exec_wc;

    // 8. Setzen der Wurzel des AST in die Datenstruktur
    data->st_node = (t_cmd *)pipe_sort_wc;
}

void	start_exec(t_data *data)
{
	if (data->st_node->type == EXECUTE)
	{
		exec_execu((t_exec *)data->st_node, data);
	}
	if (data->st_node->type == PIPE)
	{
		exec_pipe((t_pipe *)data->st_node, data);
	}
}

void	exec_pipe(t_pipe *st_node, t_data *data)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(1);
	pipe_left((t_exec *)st_node->left, pipefd, data);
	pipe_right((t_exec *)st_node->right, pipefd, data);
}

void	exec_execu(t_exec *st_node, t_data *data)
{
	char	*cmd_path;

	cmd_path = NULL;
	cmd_path = find_path(data, st_node);
	if (cmd_path == 0)
		exit(1);
	if (execve(cmd_path, st_node->argv, data->env) == -1)
		exit(1);
	free (cmd_path);
}
