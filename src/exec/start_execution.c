/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/18 17:02:45 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void fill_test_struct(t_data *data)
{
// Erstellen des 'ls -l' Befehls
t_exec *exec_ls = malloc(sizeof(t_exec));
exec_ls->type = EXECUTE;
exec_ls->argv = malloc(3 * sizeof(char *));
exec_ls->argv[0] = strdup("ls");
exec_ls->argv[1] = strdup("-l");
exec_ls->argv[2] = NULL;

// Erstellen des 'grep txt' Befehls
t_exec *exec_grep_txt = malloc(sizeof(t_exec));
exec_grep_txt->type = EXECUTE;
exec_grep_txt->argv = malloc(3 * sizeof(char *));
exec_grep_txt->argv[0] = strdup("grep");
exec_grep_txt->argv[1] = strdup("Makefile");
exec_grep_txt->argv[2] = NULL;

// Erstellen des 'cut -d " " -f 1' Befehls
t_exec *exec_cut = malloc(sizeof(t_exec));
exec_cut->type = EXECUTE;
exec_cut->argv = malloc(5 * sizeof(char *));
exec_cut->argv[0] = strdup("cut");
exec_cut->argv[1] = strdup("-d");
exec_cut->argv[2] = strdup(" ");
exec_cut->argv[3] = strdup("-f");
exec_cut->argv[4] = strdup("1");
exec_cut->argv[5] = NULL;

// Erstellen des 'wc -l' Befehls
t_exec *exec_wc = malloc(sizeof(t_exec));
exec_wc->type = EXECUTE;
exec_wc->argv = malloc(3 * sizeof(char *));
exec_wc->argv[0] = strdup("wc");
exec_wc->argv[1] = strdup("-l");
exec_wc->argv[2] = NULL;

// Erste Pipe zwischen 'ls -l' und 'grep txt'
t_pipe *pipe_ls_grep = malloc(sizeof(t_pipe));
pipe_ls_grep->type = PIPE;
pipe_ls_grep->left = (t_cmd *)exec_ls;
pipe_ls_grep->right = (t_cmd *)exec_grep_txt;

// Zweite Pipe zwischen dem Ergebnis der ersten Pipe und 'cut -d " " -f 1'
t_pipe *pipe_grep_cut = malloc(sizeof(t_pipe));
pipe_grep_cut->type = PIPE;
pipe_grep_cut->left = (t_cmd *)pipe_ls_grep;
pipe_grep_cut->right = (t_cmd *)exec_cut;

// Dritte Pipe zwischen dem Ergebnis der zweiten Pipe und 'wc -l'
t_pipe *pipe_cut_wc = malloc(sizeof(t_pipe));
pipe_cut_wc->type = PIPE;
pipe_cut_wc->left = (t_cmd *)pipe_grep_cut;
pipe_cut_wc->right = (t_cmd *)exec_wc;

// Setzen der Wurzel des AST in die Datenstruktur
data->st_node = (t_cmd *)pipe_cut_wc;
}


void	start_exec(t_data *data)
{
	if (data->st_node->type == EXECUTE)
	{
		exec_execu((t_exec *)data->st_node, data, 1);
	}
	if (data->st_node->type == PIPE)
	{
		exec_pipe((t_pipe *)data->st_node, data);
	}
}

void	exec_pipe(t_pipe *st_node, t_data *data)
{
	if (st_node->left->type == PIPE)
	{
		check_pipe((t_pipe *)st_node->left, data, 0);
	}
	else
		run_pipe((t_exec *)st_node->left, data, 0);
	dup2(data->origin_stdout, STDOUT_FILENO);
	run_pipe((t_exec *)st_node->right, data, 1);
}

void	check_pipe(t_pipe *st_node, t_data *data, int last)
{
	if (st_node->type == PIPE)
	{
		check_pipe((t_pipe *)st_node->left, data, 0);
		check_pipe((t_pipe *)st_node->right, data, last);
	}
	else
	{
		run_pipe((t_exec *)st_node, data, last);
		return ;
	}
	return ;
}

void	run_pipe(t_exec *st_node, t_data *data, int last)
{
	int		pipefd[2];
	pid_t	pid1;

	if (pipe(pipefd) == -1)
		exit(-1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (last == 0)
			dup2(pipefd[1], STDOUT_FILENO);
		else
		{
			close(pipefd[1]);
			// dup2(data->origin_stdout, STDOUT_FILENO);
		}
		exec_execu((t_exec *)st_node, data, 0);
	}
	if (pid1 > 0)
	{
		waitpid(pid1, NULL, 0);
		close(pipefd[1]);
		if (last == 0)
			dup2(pipefd[0], STDIN_FILENO);
		else
		{
			close(pipefd[0]);
			dup2(data->origin_stdin, STDIN_FILENO);
		}
	}
	return ;
}

void	exec_execu(t_exec *st_node, t_data *data, int need_child)
{
	pid_t	pid;

	data->cmd_path = find_path(data, st_node);
	if (data->cmd_path == 0)
		exit(1);
	if (need_child == 1)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			if (execve(data->cmd_path, st_node->argv, data->env) == -1)
				exit(1);
		}
		waitpid(pid, NULL, 0);
	}
	else
		if (execve(data->cmd_path, st_node->argv, data->env) == -1)
			exit(1);
	// free (cmd_path); //funktioniert nicht
}
