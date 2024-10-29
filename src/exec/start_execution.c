/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2024/10/29 15:55:20 by ymauk            ###   ########.fr       */
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

// void	fill_test_struct(t_data *data)
// {
// 	// 1. Erstellen des 'ls -l' Befehls
//     t_exec *exec_ls = malloc(sizeof(t_exec));
//     exec_ls->type = EXECUTE;
//     exec_ls->argv = malloc(3 * sizeof(char *));
//     exec_ls->argv[0] = strdup("ls");
//     exec_ls->argv[1] = strdup("-l");
//     exec_ls->argv[2] = NULL;

//     // 2. Erstellen des 'grep "txt"' Befehls
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("txt");
//     exec_grep->argv[2] = NULL;

//     // 3. Erstellen der Ausgabeumleitung '> txt_files.txt' für 'grep "txt"'
//     t_red *redir = malloc(sizeof(t_red));
//     redir->type = RED;
//     redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // steht für '>'
//     redir->file = strdup("txt_files.txt");
//     redir->fd = STDOUT_FILENO; // Standard-Ausgabe
//     redir->cmd = (t_cmd *)exec_grep; // Verweisen auf den 'grep "txt"' Befehl

//     // 4. Erstellen des PIPE-Knotens zwischen 'ls -l' und 'grep "txt" > txt_files.txt'
//     t_pipe *pipe_cmd = malloc(sizeof(t_pipe));
//     pipe_cmd->type = PIPE;
//     pipe_cmd->left = (t_cmd *)exec_ls;
//     pipe_cmd->right = (t_cmd *)redir;

//     // 5. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe_cmd;
// }


// void	fill_test_struct(t_data *data)
// {
//     // 1. Erstellen des 'cat' Befehls für den Heredoc
//     t_exec *exec_cat = malloc(sizeof(t_exec));
//     exec_cat->type = EXECUTE;
//     exec_cat->argv = malloc(3 * sizeof(char *));
//     exec_cat->argv[0] = strdup("grep");
// 	exec_cat->argv[1] = strdup("Zeile");
//     exec_cat->argv[2] = NULL;

//     // 2. Erstellen des Heredoc-Kommandos '<< EOF' für 'cat'
//     t_herd *heredoc = malloc(sizeof(t_herd));
//     heredoc->type = HEREDOC;
//     heredoc->cmd = (t_cmd *)exec_cat;  // Der `cat`-Befehl als Heredoc-Kommando
//     heredoc->del = strdup("EOF");      // Delimiter für den Heredoc

//     // 3. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)heredoc;
// }

// void fill_test_struct(t_data *data)
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("Zeile");
//     exec_grep->argv[2] = NULL;

//     // 2. Erstellen des Here-Documents '<< EOF' für `grep`
//     t_herd *heredoc = malloc(sizeof(t_herd));
//     heredoc->type = HEREDOC;
//     heredoc->cmd = (t_cmd *)exec_grep;  // Verweist auf `grep`-Kommando
//     heredoc->del = strdup("EOF");       // Delimiter für das Heredoc

//     // 3. Erstellen des `sort` Kommandos
//     t_exec *exec_sort = malloc(sizeof(t_exec));
//     exec_sort->type = EXECUTE;
//     exec_sort->argv = malloc(2 * sizeof(char *));
//     exec_sort->argv[0] = strdup("sort");
//     exec_sort->argv[1] = NULL;

//     // 4. Verbindung des Heredoc-Kommandos und `sort` mit einer Pipe
//     t_pipe *pipe = malloc(sizeof(t_pipe));
//     pipe->type = PIPE;
//     pipe->left = (t_cmd *)heredoc;     // Linkes Kommando: `grep "Zeile" << EOF`
//     pipe->right = (t_cmd *)exec_sort;  // Rechtes Kommando: `sort`

//     // 5. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe;
// }

// void fill_test_struct(t_data *data)
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("Zeile");
//     exec_grep->argv[2] = NULL;

//     // 2. Erstellen des Here-Documents '<< EOF' für `grep`
//     t_herd *heredoc = malloc(sizeof(t_herd));
//     heredoc->type = HEREDOC;
//     heredoc->cmd = (t_cmd *)exec_grep;  // Verweist auf `grep`-Kommando
//     heredoc->del = strdup("EOF");       // Delimiter für das Heredoc

//     // 3. Erstellen des `sort` Kommandos
//     t_exec *exec_sort = malloc(sizeof(t_exec));
//     exec_sort->type = EXECUTE;
//     exec_sort->argv = malloc(2 * sizeof(char *));
//     exec_sort->argv[0] = strdup("sort");
//     exec_sort->argv[1] = NULL;

//     // 4. Erstellen des `uniq` Kommandos
//     t_exec *exec_uniq = malloc(sizeof(t_exec));
//     exec_uniq->type = EXECUTE;
//     exec_uniq->argv = malloc(2 * sizeof(char *));
//     exec_uniq->argv[0] = strdup("uniq");
//     exec_uniq->argv[1] = NULL;

//     // 5. Verbindung des Here-Documents und `grep` Kommandos mit `sort` in der ersten Pipe
//     t_pipe *pipe1 = malloc(sizeof(t_pipe));
//     pipe1->type = PIPE;
//     pipe1->left = (t_cmd *)heredoc;     // Linkes Kommando: `grep "Zeile" << EOF`
//     pipe1->right = (t_cmd *)exec_sort;  // Rechtes Kommando: `sort`

//     // 6. Verbindung der ersten Pipe (`grep | sort`) mit `uniq` in der zweiten Pipe
//     t_pipe *pipe2 = malloc(sizeof(t_pipe));
//     pipe2->type = PIPE;
//     pipe2->left = (t_cmd *)pipe1;       // Linkes Kommando: `grep "Zeile" << EOF | sort`
//     pipe2->right = (t_cmd *)exec_uniq;  // Rechtes Kommando: `uniq`

//     // 7. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe2;
// }

// void fill_test_struct(t_data *data)
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("Zeile");
//     exec_grep->argv[2] = NULL;

//     // 2. Erstellen des Here-Documents '<< EOF' für `grep`
//     t_herd *heredoc = malloc(sizeof(t_herd));
//     heredoc->type = HEREDOC;
//     heredoc->cmd = (t_cmd *)exec_grep;  // Verweist auf das `grep`-Kommando
//     heredoc->del = strdup("EOF");       // Delimiter für das Here-Document

//     // 3. Erstellen des `sort` Kommandos
//     t_exec *exec_sort = malloc(sizeof(t_exec));
//     exec_sort->type = EXECUTE;
//     exec_sort->argv = malloc(2 * sizeof(char *));
//     exec_sort->argv[0] = strdup("sort");
//     exec_sort->argv[1] = NULL;

//     // 4. Erstellen des `wc -w` Kommandos
//     t_exec *exec_wc = malloc(sizeof(t_exec));
//     exec_wc->type = EXECUTE;
//     exec_wc->argv = malloc(3 * sizeof(char *));
//     exec_wc->argv[0] = strdup("wc");
//     exec_wc->argv[1] = strdup("-w");
//     exec_wc->argv[2] = NULL;

//     // 5. Erstellen des `tee result.txt` Kommandos
//     t_exec *exec_tee = malloc(sizeof(t_exec));
//     exec_tee->type = EXECUTE;
//     exec_tee->argv = malloc(3 * sizeof(char *));
//     exec_tee->argv[0] = strdup("tee");
//     exec_tee->argv[1] = strdup("result.txt");
//     exec_tee->argv[2] = NULL;

//     // 6. Verbindung von `grep` und `sort` in der ersten Pipe
//     t_pipe *pipe1 = malloc(sizeof(t_pipe));
//     pipe1->type = PIPE;
//     pipe1->left = (t_cmd *)heredoc;     // Linkes Kommando: `grep "Zeile" << EOF`
//     pipe1->right = (t_cmd *)exec_sort;  // Rechtes Kommando: `sort`

//     // 7. Verbindung der ersten Pipe (`grep | sort`) mit `wc -w` in der zweiten Pipe
//     t_pipe *pipe2 = malloc(sizeof(t_pipe));
//     pipe2->type = PIPE;
//     pipe2->left = (t_cmd *)pipe1;       // Linkes Kommando: `grep "Zeile" << EOF | sort`
//     pipe2->right = (t_cmd *)exec_wc;    // Rechtes Kommando: `wc -w`

//     // 8. Verbindung der zweiten Pipe (`grep | sort | wc -w`) mit `tee result.txt` in der dritten Pipe
//     t_pipe *pipe3 = malloc(sizeof(t_pipe));
//     pipe3->type = PIPE;
//     pipe3->left = (t_cmd *)pipe2;       // Linkes Kommando: `grep | sort | wc -w`
//     pipe3->right = (t_cmd *)exec_tee;   // Rechtes Kommando: `tee result.txt`

//     // 9. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe3;
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

    // 2. Erstellen der Ausgabeumleitung '>> test.txt' für 'ls -l'
    t_red *redir = malloc(sizeof(t_red));
    redir->type = RED;
    // redir->mode = O_WRONLY | O_CREAT | O_APPEND; // '>>' steht für anhängen
	// redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // steht für '>'
	redir->mode = O_RDONLY; // steht für '<'
    redir->file = strdup("test.txt");
    // redir->fd = STDOUT_FILENO; // Standard-Ausgabe
	redir->fd = STDIN_FILENO; // Standard-Ausgabe
    redir->cmd = (t_cmd *)exec_ls; // Verweisen auf den 'ls -l' Befehl

    // 3. Setzen der Wurzel des AST in die Datenstruktur
    data->st_node = (t_cmd *)redir;
}

void	start_exec(t_data *data, t_cmd *cmd)
{
	if (cmd->type == EXECUTE)
	{
		exec_execu((t_exec *)cmd, data);
	}
	if (cmd->type == PIPE)
	{
		exec_pipe((t_pipe *)cmd, data);
	}
	if (cmd->type == RED)
	{
		exec_red((t_red *)cmd, data);
	}
	if (cmd->type == HEREDOC)
	{
		exec_heredoc((t_herd *)cmd, data);
	}
}

void	exec_heredoc(t_herd *st_node, t_data *data)
{
	int		fd;

	fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_in_file(fd, (t_herd *)st_node);
	close (fd);
	fd = open("heredoc.txt", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(1);
	close(fd);
	exec_execu((t_exec *)st_node->cmd, data);
}

void	exec_red(t_red *st_node, t_data *data)
{
	int		fd_orig;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (-1);
	if (pid == 0)
	{
		if (st_node->fd > 0)
		{
			fd_orig = open(st_node->file, st_node->mode, 0644);
			if (fd_orig == -1)
				exit(1);
			if (dup2(fd_orig, st_node->fd) == -1)
				exit(1);
			close(fd_orig);
			exec_execu((t_exec *)st_node->cmd, data);
			if (dup2(data->origin_stdout, STDOUT_FILENO) == -1)
				exit (0);
		}
		else
		{
			fd_orig = open(st_node->file, st_node->mode);
			if (fd_orig == -1)
				exit(1);
			if (dup2(fd_orig, st_node->fd) == -1)
				exit(1);
			close(fd_orig);
			exec_execu((t_exec *)st_node->cmd, data);
			if (dup2(data->origin_stdout, STDIN_FILENO) == -1)
				exit (0);
		}
	}
	waitpid(pid, NULL, 0);
}

void	exec_execu(t_exec *st_node, t_data *data)
{
	data->cmd_path = find_path(data, st_node);
	if (data->cmd_path == 0)
		exit(1);
	if (execve(data->cmd_path, st_node->argv, data->env) == -1)
		exit(1);
	// free (cmd_path); //funktioniert nicht
}

void	exec_pipe(t_pipe *st_node, t_data *data)
{
	// if (st_node->left->type == PIPE)
	check_pipe((t_pipe *)st_node->left, data, 0);
	dup2(data->origin_stdout, STDOUT_FILENO);
	run_pipe((t_cmd *)st_node->right, data, 1);
}
