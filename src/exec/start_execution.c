/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/22 15:55:28 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void fill_test_struct(t_data *data)
// {
// 	// Erstellen des 'ls -l' Befehls
// 	t_exec *exec_ls = malloc(sizeof(t_exec));
// 	exec_ls->type = EXECUTE;
// 	exec_ls->argv = malloc(3 * sizeof(char *));
// 	exec_ls->argv[0] = strdup("ls");
// 	exec_ls->argv[1] = strdup("-l");
// 	exec_ls->argv[2] = NULL;

// 	// Erstellen des 'grep txt' Befehls
// 	t_exec *exec_grep_txt = malloc(sizeof(t_exec));
// 	exec_grep_txt->type = EXECUTE;
// 	exec_grep_txt->argv = malloc(3 * sizeof(char *));
// 	exec_grep_txt->argv[0] = strdup("grep");
// 	exec_grep_txt->argv[1] = strdup("Makefile");
// 	exec_grep_txt->argv[2] = NULL;

// 	// Erstellen des 'cut -d " " -f 1' Befehls
// 	t_exec *exec_cut = malloc(sizeof(t_exec));
// 	exec_cut->type = EXECUTE;
// 	exec_cut->argv = malloc(5 * sizeof(char *));
// 	exec_cut->argv[0] = strdup("cut");
// 	exec_cut->argv[1] = strdup("-d");
// 	exec_cut->argv[2] = strdup(" ");
// 	exec_cut->argv[3] = strdup("-f");
// 	exec_cut->argv[4] = strdup("1");
// 	exec_cut->argv[5] = NULL;

// 	// Erstellen des 'wc -l' Befehls
// 	t_exec *exec_wc = malloc(sizeof(t_exec));
// 	exec_wc->type = EXECUTE;
// 	exec_wc->argv = malloc(3 * sizeof(char *));
// 	exec_wc->argv[0] = strdup("wc");
// 	exec_wc->argv[1] = strdup("-l");
// 	exec_wc->argv[2] = NULL;

// 	// Erste Pipe zwischen 'ls -l' und 'grep txt'
// 	t_pipe *pipe_ls_grep = malloc(sizeof(t_pipe));
// 	pipe_ls_grep->type = PIPE;
// 	pipe_ls_grep->left = (t_cmd *)exec_ls;
// 	pipe_ls_grep->right = (t_cmd *)exec_grep_txt;

// 	// Zweite Pipe zwischen dem Ergebnis der ersten Pipe und 'cut -d " " -f 1'
// 	t_pipe *pipe_grep_cut = malloc(sizeof(t_pipe));
// 	pipe_grep_cut->type = PIPE;
// 	pipe_grep_cut->left = (t_cmd *)pipe_ls_grep;
// 	pipe_grep_cut->right = (t_cmd *)exec_cut;

// 	// Dritte Pipe zwischen dem Ergebnis der zweiten Pipe und 'wc -l'
// 	t_pipe *pipe_cut_wc = malloc(sizeof(t_pipe));
// 	pipe_cut_wc->type = PIPE;
// 	pipe_cut_wc->left = (t_cmd *)pipe_grep_cut;
// 	pipe_cut_wc->right = (t_cmd *)exec_wc;

// 	// Setzen der Wurzel des AST in die Datenstruktur
// 	data->st_node = (t_cmd *)pipe_cut_wc;
// }

// void fill_test_struct(t_data *data)
// {
// 	// Erstellen des 'cat Makefile' Befehls
// 	t_exec *exec_cat = malloc(sizeof(t_exec));
// 	exec_cat->type = EXECUTE;
// 	exec_cat->argv = malloc(3 * sizeof(char *));
// 	exec_cat->argv[0] = strdup("cat");
// 	exec_cat->argv[1] = strdup("Makefile");
// 	exec_cat->argv[2] = NULL;

// 	// Erstellen des 'grep all' Befehls
// 	t_exec *exec_grep = malloc(sizeof(t_exec));
// 	exec_grep->type = EXECUTE;
// 	exec_grep->argv = malloc(3 * sizeof(char *));
// 	exec_grep->argv[0] = strdup("grep");
// 	exec_grep->argv[1] = strdup("all");
// 	exec_grep->argv[2] = NULL;

// 	// Erstellen des 'wc -l' Befehls
// 	t_exec *exec_wc = malloc(sizeof(t_exec));
// 	exec_wc->type = EXECUTE;
// 	exec_wc->argv = malloc(3 * sizeof(char *));
// 	exec_wc->argv[0] = strdup("wc");
// 	exec_wc->argv[1] = strdup("-l");
// 	exec_wc->argv[2] = NULL;

// 	// Erste Pipe zwischen 'cat Makefile' und 'grep all'
// 	t_pipe *pipe_cat_grep = malloc(sizeof(t_pipe));
// 	pipe_cat_grep->type = PIPE;
// 	pipe_cat_grep->left = (t_cmd *)exec_cat;
// 	pipe_cat_grep->right = (t_cmd *)exec_grep;

// 	// Zweite Pipe zwischen dem Ergebnis der ersten Pipe und 'wc -l'
// 	t_pipe *pipe_grep_wc = malloc(sizeof(t_pipe));
// 	pipe_grep_wc->type = PIPE;
// 	pipe_grep_wc->left = (t_cmd *)pipe_cat_grep;
// 	pipe_grep_wc->right = (t_cmd *)exec_wc;

// 	// Setzen der Wurzel des AST in die Datenstruktur
// 	data->st_node = (t_cmd *)pipe_grep_wc;
// }

void	fill_test_struct(t_data *data)
{
	// 1. Erstellen des 'ls -l' Befehls
    t_exec *exec_ls = malloc(sizeof(t_exec));
    exec_ls->type = EXECUTE;
    exec_ls->argv = malloc(3 * sizeof(char *));
    exec_ls->argv[0] = strdup("ls");
    exec_ls->argv[1] = strdup("-l");
    exec_ls->argv[2] = NULL;

    // 2. Erstellen der Ausgabeumleitung '> test.txt'
    t_red *redir = malloc(sizeof(t_red));
    redir->type = RED;
	// redir->mode = O_RDONLY; // steht fúr '<'
    // redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // steht fúr '>'
	redir->mode = O_WRONLY | O_CREAT | O_APPEND; // steht fúr '>>'
    redir->file = strdup("test.txt");
	// redir->fd = STDIN_FILENO; // Standard-Ausgabe = 0
    redir->fd = STDOUT_FILENO; // Standard-Ausgabe = 1
    redir->cmd = (t_cmd *)exec_ls; // Verweisen auf den 'ls -l' Befehl

    // 3. Setzen der Wurzel des AST in die Datenstruktur
    data->st_node = (t_cmd *)redir;
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
	if (data->st_node->type == RED)
	{
		exec_red((t_red *)data->st_node, data);
	}
}

void	exec_red(t_red *st_node, t_data *data)
{
	int	fd_orig;

	fd_orig = 0;
	if (st_node->fd > 0)
	{
		fd_orig = open(st_node->file, st_node->mode, 0644);
		dup2(fd_orig, st_node->fd);
		close(fd_orig);
	}
	else
	{
		fd_orig = open(st_node->file, st_node->mode);
		dup2(fd_orig, st_node->fd);
		close(fd_orig);
	}
	exec_execu((t_exec *)st_node->cmd, data, 1);
	dup2(data->origin_stdout, STDOUT_FILENO);
	// dup2(data->origin_stdin, STDIN_FILENO);
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
