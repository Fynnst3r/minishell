/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforster <fforster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:46:35 by fforster          #+#    #+#             */
/*   Updated: 2025/01/06 23:27:51 by fforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	expand_heredoc(int fd, char *buffer, t_data *data)
{
	char	*exit_status;
	char	*expan;
	t_lexer	lex;

	lex = init_lex(NULL);
	lex.ignore_quotes = true;
	buffer[ft_strlen(buffer) - 1] = 0;
	exit_status = ft_itoa(data->e_status);
	expan = get_exp_str(buffer, exit_status, &lex, data);
	if (expan[0] == 0)
		write(fd, "\n", 1);
	else
	{
		write(fd, expan, ft_strlen(expan));
		write(fd, "\n", 1);
	}
	ft_free(expan);
	ft_free(exit_status);
}

static int	write_in_file(t_data *data, char *buffer, int fd, ssize_t bytes)
{
	t_herd	*st_node;

	st_node = (t_herd *)data->st_node;
	if (buffer[bytes -1] != '\n')
		write(STDERR_FILENO, "\n", 1);
	buffer[bytes - 1] = '\n';
	buffer[bytes] = '\0';
	if (!ft_strncmp(buffer, st_node->del, ft_strlen(st_node->del)))
		return (1);
	write(STDERR_FILENO, "heredoc> ", 9);
	if (ft_strchr(buffer, '\'')
		|| ft_strchr(buffer, '\"') || ft_strchr(buffer, '$'))
		expand_heredoc(fd, buffer, data);
	else
		write(fd, buffer, bytes);
	return (0);
}

static void	make_temporary_file(int fd, t_herd *st_node, t_data *data)
{
	ssize_t			bytes;
	char			buffer[1024];
	ssize_t			to_read;

	bytes = -1;
	to_read = sizeof buffer - 2;
	write(STDERR_FILENO, "heredoc> ", 9);
	while (1)
	{
		if (g_signal == SIGINT)
			return ;
		if (bytes > 0)
			if (write_in_file(data, buffer, fd, bytes))
				break ;
		bytes = read(STDIN_FILENO, buffer, to_read);
		while (bytes > 0 && bytes < to_read && buffer[bytes - 1] != '\n')
			bytes += read(STDIN_FILENO, buffer + bytes, to_read - bytes);
		if (bytes == 0)
		{
			write(STDERR_FILENO, "\n", 1);
			print_error("warning: here-document delimited by "
				"EOF and not the delimeter: ", st_node->del);
			break ;
		}
	}
}

static void	heredoc_helper_child(t_herd *st_node, t_data *data, bool in_pipe)
{
	int	fd;

	fd = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		clean_exit(1, true);
	make_temporary_file(fd, (t_herd *)st_node, data);
	if (g_signal == SIGINT)
		return (unlink("heredoc.txt"), close(fd), clean_exit(0, false));
	close (fd);
	fd = open("heredoc.txt", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		clean_exit(1, true);
	close(fd);
	if (st_node->cmd->type == RED)
		start_exec(data, st_node->cmd, in_pipe);
	else if (st_node->cmd->type == EXECUTE)
		exec_execu((t_exec *)st_node->cmd, data, in_pipe);
	unlink("heredoc.txt");
	clean_exit(0, false);
}

void	exec_heredoc(t_herd *st_node, t_data *data, bool in_pipe)
{
	pid_t	pid;
	int		status;

	prepare_signal(data, signal_handler3);
	pid = ft_fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		heredoc_helper_child(st_node, data, in_pipe);
	}
	while (waitpid(pid, &status, 0) == -1)
		;
	prepare_signal(data, signal_handler);
	change_e_stat(data, WEXITSTATUS(status));
	extra_exec(data, data->st_node);
}
