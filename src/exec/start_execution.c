/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:24:39 by ymauk             #+#    #+#             */
/*   Updated: 2025/01/02 21:54:51 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void fill_test_struct(t_data *data) // pwd
// {
//     t_exec *exec_pwd = malloc(sizeof(t_exec));
//     exec_pwd->type = EXECUTE;
//     exec_pwd->argv = malloc(2 * sizeof(char *));
//     exec_pwd->argv[0] = strdup("env");  // Das Kommando `pwd`
//     exec_pwd->argv[1] = NULL;           // Null-Terminierung für exec-Kompatibilität
//     data->st_node = (t_cmd *)exec_pwd;
// }

// void fill_test_struct(t_data *data) // echo hallo maus
// {
//     // 1. Erstellen des `echo hallo` Kommandos
//     t_exec *exec_echo = malloc(sizeof(t_exec));
//     exec_echo->type = EXECUTE;
//     exec_echo->argv = malloc(6 * sizeof(char *));
//     exec_echo->argv[0] = strdup("echo");   // Das Kommando `echo`
//     exec_echo->argv[1] = strdup("-nnnnnn");  // Das Argument `hallo`
//     exec_echo->argv[2] = strdup("-nnnn");  // Das Argument `hallo`
//     exec_echo->argv[3] = strdup("hallo");  // Das Argument `hallo`
//     exec_echo->argv[4] = strdup("maus");  // Das Argument `hallo`
//     exec_echo->argv[5] = NULL;             // Null-Terminierung für exec-Kompatibilität
//     // 2. Setzen des Kommandos als Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)exec_echo;
// }

// void fill_test_struct(t_data *data) // ls -l | grep Makefile | cut -d " " -f 1 | wc -l
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

// void fill_test_struct(t_data *data) // cat "Makefile" | grep "all" | wc -l
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
// 	exec_wc->argv[0] = strdup("hallo");
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

// void	fill_test_struct(t_data *data) // ls -l | grep "txt" > txt_files.txt
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

// void fill_test_struct(t_data *data) // grep "Zeile" << EOF | sort
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

// void fill_test_struct(t_data *data) // grep "Zeile" << EOF | sort | uniq
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
// void fill_test_struct(t_data *data) // grep "Zeile" << EOF | sort | uniq
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_echo = malloc(sizeof(t_exec));
//     exec_echo->type = EXECUTE;
//     exec_echo->argv = malloc(3 * sizeof(char *));
//     exec_echo->argv[0] = strdup("grep");
//     exec_echo->argv[1] = strdup("Zeile");
//     exec_echo->argv[2] = NULL;
//     // 3. Erstellen des `sort` Kommandos
//     t_exec *exec_cat = malloc(sizeof(t_exec));
//     exec_cat->type = EXECUTE;
//     exec_cat->argv = malloc(2 * sizeof(char *));
//     exec_cat->argv[0] = strdup("cat");
//     exec_cat->argv[1] = NULL;
//     // 4. Erstellen des `uniq` Kommandos
//     // 2. Erstellen des Here-Documents '<< EOF' für `grep`
//     t_herd *heredoc = malloc(sizeof(t_herd));
//     heredoc->type = HEREDOC;
//     heredoc->cmd = (t_cmd *)exec_cat;  // Verweist auf `grep`-Kommando
//     heredoc->del = strdup("end");       // Delimiter für das Heredoc
//     // t_exec *exec_uniq = malloc(sizeof(t_exec));
//     // exec_uniq->type = EXECUTE;
//     // exec_uniq->argv = malloc(2 * sizeof(char *));
//     // exec_uniq->argv[0] = strdup("uniq");
//     // exec_uniq->argv[1] = NULL;
//     // 5. Verbindung des Here-Documents und `grep` Kommandos mit `sort` in der ersten Pipe
//     t_pipe *pipe1 = malloc(sizeof(t_pipe));
//     pipe1->type = PIPE;
//     pipe1->left = (t_cmd *)exec_echo;     // Linkes Kommando: `grep "Zeile" << EOF`
//     pipe1->right = (t_herd *)heredoc;  // Rechtes Kommando: `sort`
//     // 6. Verbindung der ersten Pipe (`grep | sort`) mit `uniq` in der zweiten Pipe
//     // t_pipe *pipe2 = malloc(sizeof(t_pipe));
//     // pipe2->type = PIPE;
//     // pipe2->left = (t_cmd *)pipe1;       // Linkes Kommando: `grep "Zeile" << EOF | sort`
//     // pipe2->right = (t_cmd *)exec_uniq;  // Rechtes Kommando: `uniq`
//     // 7. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe1;
// }

// void fill_test_struct(t_data *data) // grep "Zeile" << EOF | sort | wc -w | tee result.txt
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

// void	fill_test_struct(t_data *data) // grep "Zeile" < input.txt
// {
//     // 1. Erstellen des 'ls -l' Befehls
//     t_exec *exec_ls = malloc(sizeof(t_exec));
//     exec_ls->type = EXECUTE;
//     exec_ls->argv = malloc(3 * sizeof(char *));
//     exec_ls->argv[0] = strdup("grep");
//     exec_ls->argv[1] = strdup("Zeile");
//     exec_ls->argv[2] = NULL;
//     // 2. Erstellen der Ausgabeumleitung '>> test.txt' für 'ls -l'
//     t_red *redir = malloc(sizeof(t_red));
//     redir->type = RED;
//     // redir->mode = O_WRONLY | O_CREAT | O_APPEND; // '>>' steht für anhängen
// 	// redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // steht für '>'
// 	redir->mode = O_RDONLY; // steht für '<'
//     redir->file = strdup("input.txt");
//     // redir->fd = STDOUT_FILENO; // Standard-Ausgabe
// 	redir->fd = STDIN_FILENO; // Standard-Ausgabe
//     redir->cmd = (t_cmd *)exec_ls; // Verweisen auf den 'ls -l' Befehl
//     // 3. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)redir;
// }

// void fill_test_struct(t_data *data) // grep "Zeile" < input.txt | sort | uniq > output.txt
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("Zeile");
//     exec_grep->argv[2] = NULL;
//     // 2. Erstellen der Eingaberedirection '< input.txt' für `grep`
//     t_red *input_redir = malloc(sizeof(t_red));
//     input_redir->type = RED;
//     input_redir->mode = O_RDONLY;         // Modus für '<'
//     input_redir->file = strdup("input.txt");
//     input_redir->fd = STDIN_FILENO;
//     input_redir->cmd = (t_cmd *)exec_grep; // `grep` als zugeordnetes Kommando
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
//     // 5. Erstellen der Ausgaberichtung '> output.txt' für `uniq`
//     t_red *output_redir = malloc(sizeof(t_red));
//     output_redir->type = RED;
//     output_redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // Modus für '>'
//     output_redir->file = strdup("output.txt");
//     output_redir->fd = STDOUT_FILENO;
//     output_redir->cmd = (t_cmd *)exec_uniq; // `uniq` als zugeordnetes Kommando
//     // 6. Verbindung von `grep` (mit Eingaberedirection) und `sort` in der ersten Pipe
//     t_pipe *pipe1 = malloc(sizeof(t_pipe));
//     pipe1->type = PIPE;
//     pipe1->left = (t_cmd *)input_redir; // Linkes Kommando: `grep "Zeile" < input.txt`
//     pipe1->right = (t_cmd *)exec_sort;  // Rechtes Kommando: `sort`
//     // 7. Verbindung der ersten Pipe (`grep | sort`) mit `uniq` (mit Ausgaberichtung) in der zweiten Pipe
//     t_pipe *pipe2 = malloc(sizeof(t_pipe));
//     pipe2->type = PIPE;
//     pipe2->left = (t_cmd *)pipe1;       // Linkes Kommando: `grep | sort`
//     pipe2->right = (t_cmd *)output_redir; // Rechtes Kommando: `uniq > output.txt`
//     // 8. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe2;
// }

// void fill_test_struct(t_data *data) // grep "Zeile" < input.txt | sort | uniq
// {
//     // 1. Erstellen des `grep "Zeile"` Kommandos
//     t_exec *exec_grep = malloc(sizeof(t_exec));
//     exec_grep->type = EXECUTE;
//     exec_grep->argv = malloc(3 * sizeof(char *));
//     exec_grep->argv[0] = strdup("grep");
//     exec_grep->argv[1] = strdup("Zeile");
//     exec_grep->argv[2] = NULL;
//     // 2. Erstellen der Eingaberedirection '< input.txt' für `grep`
//     t_red *input_redir = malloc(sizeof(t_red));
//     input_redir->type = RED;
//     input_redir->mode = O_RDONLY;         // Modus für '<'
//     input_redir->file = strdup("input.txt");
//     input_redir->fd = STDIN_FILENO;
//     input_redir->cmd = (t_cmd *)exec_grep; // `grep` als zugeordnetes Kommando
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
//     // 5. Verbindung von `grep` (mit Eingaberedirection) und `sort` in der ersten Pipe
//     t_pipe *pipe1 = malloc(sizeof(t_pipe));
//     pipe1->type = PIPE;
//     pipe1->left = (t_cmd *)input_redir; // Linkes Kommando: `grep "Zeile" < input.txt`
//     pipe1->right = (t_cmd *)exec_sort;  // Rechtes Kommando: `sort`
//     // 6. Verbindung der ersten Pipe (`grep | sort`) mit `uniq` in der zweiten Pipe
//     t_pipe *pipe2 = malloc(sizeof(t_pipe));
//     pipe2->type = PIPE;
//     pipe2->left = (t_cmd *)pipe1;       // Linkes Kommando: `grep | sort`
//     pipe2->right = (t_cmd *)exec_uniq;  // Rechtes Kommando: `uniq`
//     // 7. Setzen der Wurzel des AST in die Datenstruktur
//     data->st_node = (t_cmd *)pipe2;
// }

// void fill_test_struct(t_data *data) // echo hallo > input.txt
// {
//     // 1. Create the 'echo' command
//     t_exec *exec_echo = malloc(sizeof(t_exec));
//     exec_echo->type = EXECUTE;
//     exec_echo->argv = malloc(3 * sizeof(char *));
//     exec_echo->argv[0] = strdup("echo");
//     exec_echo->argv[1] = strdup("hallo");
//     exec_echo->argv[2] = NULL;
//     // 2. Create the output redirection '> input.txt' for 'echo hallo'
//     t_red *redir = malloc(sizeof(t_red));
//     redir->type = RED;
//     redir->mode = O_WRONLY | O_CREAT | O_TRUNC; // '>' means overwrite
//     redir->file = strdup("input.txt");
//     redir->fd = STDOUT_FILENO; // Standard output
//     redir->cmd = (t_cmd *)exec_echo; // Point to the 'echo' command
//     // 3. Set the root of the AST in the data structure
//     data->st_node = (t_cmd *)redir;
// }

// void fill_test_struct(t_data *data) // echo "hallo" > a > b > c
// {
//     // 1. Erstellen des echo-Befehls mit Argument "hallo"
//     t_exec *exec_echo = malloc(sizeof(t_exec));
//     exec_echo->type = EXECUTE;
//     exec_echo->argv = malloc(3 * sizeof(char *));
//     exec_echo->argv[0] = strdup("echo");
//     exec_echo->argv[1] = strdup("hallo");
//     exec_echo->argv[2] = NULL;
//     // 2. Erste Ausgabeumleitung '> a'
//     t_red *redir_a = malloc(sizeof(t_red));
//     redir_a->type = RED;
//     redir_a->mode = O_WRONLY | O_CREAT | O_TRUNC;
//     redir_a->file = strdup("a");
//     redir_a->fd = STDOUT_FILENO;
//     // 3. Zweite Ausgabeumleitung '> b'
//     t_red *redir_b = malloc(sizeof(t_red));
//     redir_b->type = RED;
//     redir_b->mode = O_WRONLY | O_CREAT | O_TRUNC;
//     redir_b->file = strdup("b");
//     redir_b->fd = STDOUT_FILENO;
//     // 4. Dritte Ausgabeumleitung '> c'
//     t_red *redir_c = malloc(sizeof(t_red));
//     redir_c->type = RED;
//     redir_c->mode = O_WRONLY | O_CREAT | O_TRUNC;
//     redir_c->file = strdup("c");
//     redir_c->fd = STDOUT_FILENO;
//     // 5. Verkettung der Redirections in der Reihenfolge der Eingabe:
//     // Dadurch wird zuerst a, dann b, dann c gesetzt, bevor echo ausgeführt wird.
//     redir_c->cmd = (t_cmd *)exec_echo; // c verweist auf den echo-Befehl
//     redir_b->cmd = (t_cmd *)redir_c;   // b verweist auf c
//     redir_a->cmd = (t_cmd *)redir_b;   // a verweist auf b
//     // Letztendlich ist a die Wurzel des AST, da a die erste Umleitung ist
//     data->st_node = (t_cmd *)redir_a;
// }

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
	pid_t	pid;
	int		status;

	prepare_signal(data, signal_handler2);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("YM_FF_SHELL");
			exit(1);
		}
		if (write_in_file(fd, (t_herd *)st_node, data) == 1)
		{
			unlink("heredoc.txt");
			close(fd);
			exit(1);
		}
		close (fd);
		fd = open("heredoc.txt", O_RDONLY);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("herd");
			exit(1);
		}
		close(fd);
		if (st_node->cmd->type == RED)
			start_exec(data, st_node->cmd);
		else if (st_node->cmd->type == EXECUTE)
			exec_execu((t_exec *)st_node->cmd, data);
		unlink("heredoc.txt");
		exit(1);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	prepare_signal(data, signal_handler);
	data->e_status = WEXITSTATUS(status);
	extra_exec(data, data->st_node);
}

void	exec_red(t_red *st_node, t_data *data)
{
	int		fd_orig;
	int		saved_fd;
	pid_t	pid;
	int		status;

	prepare_signal(data, signal_handler2);
	pid = fork();
	if (pid == -1)
	{
		perror("YM_FF_SHELL");
		return ;
	}
	if (pid == 0)
	{
		if (st_node->fd > 0)
		{
			fd_orig = open(st_node->file, st_node->mode, 0644);
			saved_fd = dup(st_node->fd);
		}
		else
			fd_orig = open(st_node->file, st_node->mode);
		if (fd_orig == -1)
		{
			perror("YM_FF_SHELL");
			exit(1);
		}
		if (dup2(fd_orig, st_node->fd) == -1)
			exit(1);
		close(fd_orig);
		if (st_node->cmd->type == RED)
			start_exec(data, st_node->cmd);
		else if (st_node->cmd->type == EXECUTE)
			exec_execu((t_exec *)st_node->cmd, data);
		if (dup2(saved_fd, STDOUT_FILENO) == -1)
			exit(1);
		close(saved_fd);
		exit(0);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	prepare_signal(data, signal_handler);
	data->e_status = WEXITSTATUS(status);
	extra_exec(data, data->st_node);
}

void	exec_execu(t_exec *st_node, t_data *data)
{
	pid_t		pid;
	int			status;

	if (check_builtins(data, st_node->argv) == 0)
	{
		data->cmd_path = find_path(data, st_node);
		if (data->cmd_path == 0)
			return ;
		prepare_signal(data, signal_handler2);
		pid = fork();
		if (pid == -1)
		{
			perror("YM_FF_SHELL");
			return ;
		}
		if (pid == 0)
		{
			data->env = env_list_to_array(data);
			if (execve(data->cmd_path, st_node->argv, data->env) == -1)
			{
				perror("YM_FF_SHELL");
				exit(127);
			}
		}
		while (waitpid(pid, &status, 0) == -1)
			;
		prepare_signal(data, signal_handler);
		data->e_status = WEXITSTATUS(status);
		// printf("%d exit statd\n", WEXITSTATUS(status));
		// printf("%d termsig\n", WTERMSIG(status));
		// if (WTERMSIG(status) == 0)
		// 	ft_error(NULL, 0, NULL);
		ft_free(data->cmd_path);
		return ;
	}
}

void	exec_pipe(t_pipe *st_node, t_data *data)
{
	check_pipe((t_pipe *)st_node->left, data, 0);
	dup2(data->origin_stdout, STDOUT_FILENO);
	run_pipe((t_cmd *)st_node->right, data, 1);
	// printf("pipe done\n");
	// exit(0);
}
